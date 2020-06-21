
#include <M5Atom.h>
#include <driver/i2s.h>
#include "AquesTalkTTS.h"
#include "driver/dac.h"

void setup() {
  M5.begin(true, false, true);
  M5.dis.drawpix(0, CRGB(128, 0, 0));

  int iret = TTS.create(NULL);

}

void loop() {
  M5.update();
  M5.dis.drawpix(0, CRGB(128, 0, 0));
  if(M5.Btn.wasPressed()) {
    TTS.play("emufaibu,atomu,tanoshiiyo", 20);
    M5.dis.drawpix(0, CRGB(128, 128, 128));
    Serial.printf("Free Heap Size = %d\n", esp_get_free_heap_size());
  }

}
