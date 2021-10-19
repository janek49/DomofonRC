#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <UnitecRCSwitch.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

UnitecRCSwitch rc433;
UnitecRCSwitch::ButtonCodes codes = {
  {9937264, 10142384, 9836848, 10394944}, // Button A ON codes
  {9519888, 10319760, 9604768, 10442272}, // Button A OFF codes
  {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
};

void setup() {
  rc433.setBtnCodes(&codes);
  rc433.enableTransmit(6);

  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  digitalWrite(4, 1);

  unsigned long timeNow = millis();
  while (timeNow + 4000 > millis()) {
    const char text[] = "JBC_CMD_OPEN_DOOR";
    radio.write(&text, sizeof(text));
  }

  digitalWrite(4, 0);
  digitalWrite(5, 1);

}

void loop() {
  rc433.switchOff(UnitecRCSwitch::SOCKET_A);
  delay(200);
}
