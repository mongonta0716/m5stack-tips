#pragma mark - Depend ESP8266Audio and ESP8266_Spiram libraries
/* 
cd ~/Arduino/libraries
git clone https://github.com/earlephilhower/ESP8266Audio
git clone https://github.com/Gianbacchio/ESP8266_Spiram
*/


#include <M5Core2.h>
#include <driver/i2s.h>
#include <WiFi.h>
#include "AudioFileSourceSD.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"


AudioGeneratorWAV *wav;
AudioFileSourceSD *file;
AudioOutputI2S *out;

#define OUTPUT_GAIN 50

void setup()
{
  M5.begin();
  M5.Axp.SetSpkEnable(true);

  WiFi.mode(WIFI_OFF); 
  delay(500);
  
  M5.Lcd.setTextFont(2);
  M5.Lcd.printf("Sample WAV playback begins...\n");
  Serial.printf("Sample WAV playback begins...\n");

  file = new AudioFileSourceSD("/wav/samba.wav");
  out = new AudioOutputI2S(0, 0); // Output to ExternalDAC
  out->SetPinout(12, 0, 2);
  out->SetOutputModeMono(true);
  out->SetGain((float)OUTPUT_GAIN/100.0);
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);
}

void loop()
{
  if (wav->isRunning()) {
    if (!wav->loop()) wav->stop();
  } else {
    Serial.printf("WAV done\n");
    delay(1000);
  }
}
