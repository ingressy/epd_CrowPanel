#include <Arduino.h>
#include <Preferences.h>
#include <nvs_flash.h>

Preferences prefs;

String ssid = "";
String password = "";
String mqttserver = "";
uint16_t mqttport = 1883;
uint16_t id = 0x0A;

void setup() {
    nvs_flash_erase();
    nvs_flash_init(); 

    prefs.begin("wlan", false);
    prefs.putString("ssid", ssid);
    prefs.putString("password", password);
    prefs.end();

    prefs.begin("mqtt", false);
    prefs.putString("server", mqttserver);
    prefs.putUShort("port", mqttport);
    prefs.end();

    prefs.begin("id", false);
    prefs.putUChar("number", id);
    prefs.end();
}

void loop() {

}