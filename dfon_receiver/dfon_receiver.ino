#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

const char keyphrase[] = "JBC_CMD_OPEN_DOOR";

void setup() {
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT); 
  digitalWrite(4,1);
}

void loop() {
  digitalWrite(4,1);
  digitalWrite(3, 0);
  if (radio.available()) {
    char text[17] = "";
    
    while (radio.available())
      radio.read(&text, sizeof(text));

    if (strcmp(text, keyphrase) == 0) {
      
  radio.stopListening();
  
      digitalWrite(3, 1);
      delay(100);
      digitalWrite(3, 0);

      digitalWrite(2, 1);
      digitalWrite(4, 0);

      delay(6000);

      digitalWrite(4, 1);
      digitalWrite(2, 0);


  radio.startListening();
  
    }

  }
}
