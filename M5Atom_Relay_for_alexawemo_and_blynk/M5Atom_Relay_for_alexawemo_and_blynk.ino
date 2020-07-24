/*
 * for M5Atom Lite & M5Stack RELAY Unit
 * Require
 * 
 * Blynk for ESP32
 * esp32-alexa-wemo-emulator https://github.com/mongonta0716/esp32-alexa-wemo-emulator 
 */

#include <M5Atom.h>
#include <WiFi.h>

// for Blink
#include <BlynkSimpleEsp32.h>

// for esp32-wemo-emulator
#include "WemoSwitch.h"
#include "WemoManager.h"
#include "CallbackFunction.h"

#define WARNING_COLOR 0x00ff00 
#define NORMAL_COLOR 0xff0000
#define ACTION_COLOR 0x0000ff

#define RELAY_ON HIGH
#define RELAY_OFF LOW

// prototypes
boolean connectWifi();

//on/off callbacks
void deviceOn();
void deviceOff();
void deviceStatus();

WemoManager wemoManager;
WemoSwitch *device = NULL;

//------- Replace the following! ------
char ssid[] = "Your SSID";       // your network SSID (name)
char password[] = "Your password";  // your network key

char auth[] = "Your Auto token"; // M5Atom Lite Auth token of Blynk Live

const int relayPin1 = 26;

int switch_button = 0;

void wifiConnected()
{
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  M5.dis.drawpix(0, NORMAL_COLOR);

}

BLYNK_WRITE(V0) {
  switch_button = param.asInt();
  if (switch_button == 1) {
    M5.dis.drawpix(0, ACTION_COLOR);
    digitalWrite(relayPin1, RELAY_ON);
    // deviceOn();
  } else {
    M5.dis.drawpix(0, NORMAL_COLOR);
    digitalWrite(relayPin1, RELAY_OFF);
  }
}

void setup()
{
  M5.begin(true, false, true);
  delay(10);
  M5.dis.drawpix(0, 0xFFFFFF);

  // Relay Unit (turn off)
  pinMode(relayPin1, OUTPUT);
  delay(1);
  digitalWrite(relayPin1, RELAY_OFF);
  
  Serial.begin(115200);
  Serial.println("-----------------------------");
  Serial.println("ESP02 Wemo and Blynk Controll");

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    M5.dis.drawpix(0, WARNING_COLOR);
    Serial.print(".");
    delay(500);
    M5.dis.drawpix(0, 0x000000);
    delay(500);
  }

  wifiConnected();

  wemoManager.begin();
  // Format: Alexa invocation name, local port no, on callback, off callback
  device = new WemoSwitch("Server" , 80, deviceOn, deviceOff, deviceStatus);
  wemoManager.addDevice(*device);
  delay(10);

  M5.dis.drawpix(0, WARNING_COLOR);
  Blynk.begin(auth, ssid, password);
  M5.dis.drawpix(0, NORMAL_COLOR);

}


void loop()
{
  M5.update();
  if (M5.Btn.isPressed()) {
    M5.dis.drawpix(0, ACTION_COLOR);
    digitalWrite(relayPin1, RELAY_ON);
  } else {
    M5.dis.drawpix(0, NORMAL_COLOR);
    digitalWrite(relayPin1, RELAY_OFF);
  }
  wemoManager.serverLoop();

  if (Blynk.connected()) {
    Blynk.run();
  } else {
    Serial.println("WiFi disconnected");
    M5.dis.drawpix(0, WARNING_COLOR);
    Blynk.begin(auth, ssid, password);
    Serial.println("ESP.restart()");
    ESP.restart();
  }
}

void deviceOn() {
    Serial.println("Switch 1 turn on ...");
    M5.dis.drawpix(0, ACTION_COLOR);
    digitalWrite(relayPin1, RELAY_ON);
    delay(500);
    M5.dis.drawpix(0, NORMAL_COLOR);
    digitalWrite(relayPin1, RELAY_OFF);
}

void deviceOff() {
    // Since the off state is controlled by PC, nothing is done.
    Serial.println("Switch 1 turn off ...");
    M5.dis.drawpix(0, ACTION_COLOR);
    digitalWrite(relayPin1, RELAY_ON);
    delay(500);
    M5.dis.drawpix(0, NORMAL_COLOR);
    digitalWrite(relayPin1, RELAY_OFF);
}

void deviceStatus() {
  String sts = device->getDeviceStatus(); 
}
