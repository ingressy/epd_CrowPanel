#include <WiFi.h>
#include <PubSubClient.h>
#include <Preferences.h>
#include <header.h>
#include "epd/EPD.h"
#include "epd/EPD_GUI.h"

#define DOORSIGN_HEIGHT 300
#define DOORSIGN_WIDTH 400

uint8_t* imageBuffer = nullptr;
const int IMAGE_SIZE = 400 * 300 / 8;  // = 15000 Bytes

char server[32];
uint16_t port;

void callback(char* topic, byte* payload, unsigned int length);

bool loadMQTTData() {
    if (!prefs.begin("mqtt", true)) {
        return false;
    }
    
    if (!prefs.isKey("server") || !prefs.isKey("port")) {
        prefs.end();
        return false;
    }

    //laed wlan daten aus den nvs
    prefs.begin("mqtt", true);
    prefs.getString("server", server, sizeof(server));
    port = prefs.getUShort("port", 1883);
    prefs.end();
    return true;
}

void connectMQTT() {
    if (!loadMQTTData()) {
        MQTTErrorPicture();
        return;
    }

    mqtt.setServer(server, port);
    mqtt.setCallback(callback);
    mqtt.setBufferSize(16000); 
}

void callback(char* topic, byte* payload, unsigned int length) {
    imageBuffer = (uint8_t*)ps_malloc(IMAGE_SIZE);
    if (String(topic) == "epaper/image") {
        if (length == IMAGE_SIZE) {
            memcpy(imageBuffer, payload, length);
      
            Serial.println("Bild empfangen, zeige an...");
            EPD_Init();
            EPD_Clear();
            EPD_Display(imageBuffer);
            EPD_Sleep();
        } else {
        Serial.printf("Falsche Größe: %d Bytes (erwartet: %d)\n", length, IMAGE_SIZE);
        }
    }
}