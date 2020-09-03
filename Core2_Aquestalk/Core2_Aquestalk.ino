
#include <M5Core2.h>
#include <driver/i2s.h>
#include "AquesTalkTTS.h"
#include "driver/dac.h"

void setup() {
  M5.begin();
  M5.Lcd.init();
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("AquesTalk Test");

  int iret = TTS.create(NULL);

  TTS.play("emufaibu,sutakku,koatsu-,tanoshiiyo", 20);
  Serial.printf("Free Heap Size = %d\n", esp_get_free_heap_size());

}

void loop() {

}
