#include <WiFi.h>


const char* ssid = "DoorSign";
const char* password = "UPmevGb!keScmM$j";

void connectWifi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    
}