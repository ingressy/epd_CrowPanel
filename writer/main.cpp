#include <Arduino.h>
#include <Preferences.h>
#include <nvs_flash.h>

Preferences prefs;

String ssid = "";
String password = "";

void setup() {
    nvs_flash_erase();
    nvs_flash_init(); 

    prefs.begin("wlan", false);
    prefs.putString("ssid", ssid);
    prefs.putString("password", password);
    prefs.end();
}

void loop() {

}