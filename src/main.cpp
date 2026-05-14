#include <Arduino.h>
#include <Preferences.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include "header.h"
#include "epd/EPD.h"
#include "epd/EPD_GUI.h"


Preferences prefs;
WiFiClient espClient;
PubSubClient mqtt(espClient);


void setup() {
    Serial.begin(115200);
    epd_poweron();
    //EPD_Clear();

    connectWifi();
    connectMQTT();
}



void loop() {
  if (!mqtt.connected()) {
    connectMQTT();
  }
  mqtt.loop();
}

