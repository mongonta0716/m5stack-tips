#include <M5Stack.h>
#include <M5StackUpdater.h>
#include <Wire.h>

#define SLAVE_ADDR 0x22
#define NUM_BYTES 4

byte data[NUM_BYTES] = { 0 };
byte bytesReceived = 0;


void setup() {
  M5.begin();
  Wire.begin();
  if(digitalRead(BUTTON_A_PIN) == 0) {
    Serial.println("Will Load menu binary");
    updateFromFS(SD);
    ESP.restart();
  }
  M5.Lcd.setTextSize(3);
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.println("I2C Master");
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(1);
    Wire.endTransmission();
  }
  if (M5.BtnB.wasPressed()) {
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(2);
    Wire.endTransmission();
  }
  if (M5.BtnC.wasPressed()) {
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.endTransmission();
  }
  Wire.requestFrom(SLAVE_ADDR, NUM_BYTES);
  M5.Lcd.setCursor(0,100);
  byte bytesReceived = 0;
  if (bytesReceived == NUM_BYTES) {
    for (byte i=0; i<NUM_BYTES; i++) {
      data[i] = Wire.read();
      M5.Lcd.printf("Num%d:data:%d:", i, data[i]);    
    }
  }
}
