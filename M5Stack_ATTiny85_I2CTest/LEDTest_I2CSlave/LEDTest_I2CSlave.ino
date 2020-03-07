#include <TinyWireS.h>

#define LED_PIN 1
#define FAN_PIN 4
#define SLAVE_ADDR 0x22

boolean trig = false;
uint8_t note = 0x0;

void sendEvent() {
  for(byte i=0; i<3; i++) {
    TinyWireS.send(i);
  }
}

void receiveEvent(uint8_t howMany) {
  if(TinyWireS.available()) {
    note = TinyWireS.receive();
    if (note > 0) {
      trig = true;
    } else {
      trig = false;
    }
  }
}

void setup() {
  TinyWireS.begin(SLAVE_ADDR);
  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(sendEvent);
  pinMode(LED_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
}

void loop() {
  delay(5);
  if (trig) {
    for(int i=0; i<note; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    }
    digitalWrite(FAN_PIN, HIGH);
  } else {
    for(int i=0; i<2; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(250);
      digitalWrite(LED_PIN, LOW);
      delay(250);
    }
    digitalWrite(FAN_PIN, LOW);
  }
  delay(1000);
}
