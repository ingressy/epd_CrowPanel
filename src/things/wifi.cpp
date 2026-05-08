#include <WiFi.h>
#include <Preferences.h>

Preferences prefs;
char ssid[32];
char password[64];


void loadWifiData() {
    //laed wlan daten aus den nvs
    prefs.begin("wlan", true);
    prefs.getString("ssid", ssid, sizeof(ssid));
    prefs.getString("password", password, sizeof(password));
    prefs.end();
}

void connectWifi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    
}