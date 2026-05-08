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
    epd_poweron();
    EPD_Clear();

    connectWifi();
    connectMQTT();

    Serial.begin(115200);
}



void loop() {
  if (!mqtt.connected()) {
    mqtt.connect("epaper_display");
    mqtt.subscribe("epaper/image");
  }
  mqtt.loop();
}

