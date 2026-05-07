#include <WiFi.h>


const char* ssid = "";
const char* password = "";

void connectWifi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    
}