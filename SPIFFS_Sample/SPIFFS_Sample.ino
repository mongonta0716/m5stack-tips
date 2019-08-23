#include <M5Stack.h>
#include <M5StackUpdater.h>

File file;
String filename = "/spiffs.tmp";

void setup()
{
  M5.begin();
  Wire.begin();
  if(digitalRead(BUTTON_A_PIN) == 0) {
    Serial.println("Will Load menu binary");
    updateFromFS(SD);
    ESP.restart();
  }
  M5.Lcd.println("FileReadWriteTest");
  SPIFFS.begin();
  file = SPIFFS.open(filename);
  unsigned long filesize = file.size();
  if (filesize == 0) {
    file.close();
    M5.Lcd.println("Create File");
    file = SPIFFS.open(filename, FILE_WRITE);
    file.println("Test");
    file.println(0);
    file.close();
  } else {
    M5.Lcd.println("File Read");
    String tmpstr = file.readStringUntil('\n');
    M5.Lcd.println(tmpstr);
    String numstr = file.readStringUntil('\n');
    file.close();

    int num = numstr.toInt();
    num = num + 1;
    M5.Lcd.printf("number:%d\n", num);

    M5.Lcd.println("File Write");
    file = SPIFFS.open(filename, FILE_WRITE);
    file.println("Test");
    file.println(num);
    file.close();
  }
}

void loop()
{
}
