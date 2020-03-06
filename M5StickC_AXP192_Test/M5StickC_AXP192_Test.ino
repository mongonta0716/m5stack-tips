// *********** Usage ***************
// Modify config.h before compiling.
// 
// Filename       : M5StickC_AXP192_Test.ino
// Description    : Sample to notify LINENotify via IFTTT when battery operated
// Author         : Takao Akaki
// Website        : https://raspberrypi.mongonta.com
// Update         : 2020/3/2

#include <M5StickC.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "config.h"
#include "certificate.h"

const char* server = "maker.ifttt.com";

float ibat,vbus;
WiFiClientSecure client;


void setup() {
  M5.begin();
  Wire.begin();
  Serial.begin(115200);
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(0, 50);
  ibat = M5.Axp.GetBatCurrent();
  vext = M5.Axp.GetVinVoltage();
  vusb = M5.Axp.GetVBusVoltage();
  M5.Lcd.printf("%.2f:", ibat);
  M5.Lcd.printf("%.2f:", vext);
  M5.Lcd.printf("%.2f", vusb);
  Serial.printf("%.2f:", ibat);
  Serial.printf("%.2f:", vext);
  Serial.printf("%.2f", vusb);
  Serial.printf(" Temp :%6.1f\n", M5.Axp.GetTempInAXP192());  // AXP192の内部温度

  
  
  send("Start", "", clientName);
  delay(2000);
  M5.Lcd.fillScreen(TFT_BLACK);
  
}

void send(String val1, String val2, String val3) {

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      M5.Lcd.print(".");
    }
  }

  client.setCACert(test_ca_cert);

  Serial.println("\nStarting connection to server...");
  if (!client.connect(server, 443)) {
    Serial.println("Connection failed!");
    M5.Lcd.setCursor(0, 150);
    M5.Lcd.print("Connection failed");
    
  } else {
    M5.Lcd.setCursor(0, 150);
    M5.Lcd.print("Connected");
    Serial.println("Connected to server!");
    // Make a HTTP request:
    String url = "/trigger/" + makerEvent + "/with/key/" + makerKey;
    url += "?value1=" + val1 + "&value2=" + val2 + "&value3=" + val3;
    Serial.printf("url:%s\n", url);
    client.println("GET " + url + " HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();

    Serial.print("Waiting for response "); //WiFiClientSecure uses a non blocking implementation

    int count = 0;
    while (!client.available()) {
      delay(50); //
      Serial.print(".");

      count++;
      if (count > 20 * 20) { // about 20s
        Serial.println("(send) failed!");
        return;
      }
    }
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }

    // if the server's disconnected, stop the client:
    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting from server.");
      client.stop();
    }
  }
  WiFi.disconnect();
}

bool batteryNone = false;
uint32_t targetTime = 0;

void loop() {
  M5.Lcd.setRotation(0);
  M5.Lcd.setCursor(0,0);

  M5.Lcd.printf("AXP192 Test\n");
  M5.Lcd.printf("\n");
 
  M5.Lcd.printf("Battery\n");
  M5.Lcd.printf(" State:%6d\n"  , M5.Axp.GetBatState());      // バッテリーが接続されているか(常に1のはず)
  M5.Lcd.printf(" Warn :%6d\n"  , M5.Axp.GetWarningLevel());  // バッテリー残量警告 0:残あり, 1:残なし
  M5.Lcd.printf(" Temp :%6.1f\n", M5.Axp.GetTempInAXP192());  // AXP192の内部温度
  M5.Lcd.printf(" V(V) :%6.3f\n", M5.Axp.GetBatVoltage());    // バッテリー電圧(3.0V-4.2V程度)
  M5.Lcd.printf(" I(mA):%6.3f\n", M5.Axp.GetBatCurrent());    // バッテリー電流(プラスが充電、マイナスが放電)
  M5.Lcd.printf(" W(mW):%6.3f\n", M5.Axp.GetBatPower());      // バッテリー電力(W=V*abs(I))
 
  M5.Lcd.printf("ASP\n");
  M5.Lcd.printf(" V(V) :%6.3f\n", M5.Axp.GetAPSVoltage());    // ESP32に供給されている電圧
 
  M5.Lcd.printf("VBus(USB)\n");
  M5.Lcd.printf(" V(V) :%6.3f\n", M5.Axp.GetVBusVoltage());   // USB電源からの電圧
  M5.Lcd.printf(" I(mA):%6.3f\n", M5.Axp.GetVBusCurrent());   // USB電源からの電流
 
  M5.Lcd.printf("VIN(5V-In)\n");
  M5.Lcd.printf(" V(V) :%6.3f\n", M5.Axp.GetVinVoltage());    // 5V IN端子からの電圧
  M5.Lcd.printf(" I(mA):%6.3f\n", M5.Axp.GetVinCurrent());    // 5V IN端子からの電流

  ibat = M5.Axp.GetBatCurrent();
  vbus = M5.Axp.GetVBusVoltage();
  if (!batteryNone) {
    if ((ibat < 0) && (vbus < 4)) {
      batteryNone = true;
      float vbat = M5.Axp.GetBatVoltage();
      send("BatteryNone", "Bat:" + String(vbat) + "V", clientName);
      M5.Lcd.setCursor(0, 150);
      M5.Lcd.print("ExtPowerOff");

      targetTime = millis() + 3 * 60 * 1000; // Wait send
    }
  } else if (targetTime < millis()) {
      batteryNone = false;
      M5.Lcd.setCursor(0, 150);
      M5.Lcd.print("ExtPower On");
  }

  delay(1000);
  
}
