#include <WiFi.h>
#include <Preferences.h>
#include <header.h>

char ssid[32];
char password[64];


bool loadWifiData() {
    if (!prefs.begin("wlan", true)) {
        return false;
    }
    
    if (!prefs.isKey("ssid") || !prefs.isKey("password")) {
        prefs.end();
        return false;
    }

    //laed wlan daten aus den nvs
    prefs.begin("wlan", true);
    prefs.getString("ssid", ssid, sizeof(ssid));
    prefs.getString("password", password, sizeof(password));
    prefs.end();
    return true;
}

void connectWifi() {
    if (!loadWifiData()) {
        WifiErrorPicture();
        return;
    }

    WiFi.begin(ssid, password);

    int versuche = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        versuche++;
        if (versuche > 120) {
            WifiErrorPicture();
            return;
        }
    }
}