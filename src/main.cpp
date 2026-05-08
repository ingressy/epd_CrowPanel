#include <Arduino.h>
#include "header.h"
#include "epd/EPD.h"
#include "epd/EPD_GUI.h"
#include <WiFi.h>
#include <PubSubClient.h>

uint8_t Image_BW[15000];

#define DOORSIGN_HEIGHT 300
#define DOORSIGN_WIDTH 400

uint8_t* imageBuffer = nullptr;
const int IMAGE_SIZE = 400 * 300 / 8;  // = 15000 Bytes

WiFiClient espClient;
PubSubClient client(espClient);

const char* mqtt_server = "192.168.103.105";

void callback(char* topic, byte* payload, unsigned int length) {
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

void setup() {
    epd_poweron();
    
    loadWifiData();
    connectWifi();

    Serial.begin(115200);
    Serial.println("EPD inited!");

    EPD_Clear();
    //Paint_NewImage(Image_BW, EPD_W, EPD_H, 0, WHITE); // Create a new image buffer with size EPD_W x EPD_H and background color white.
    //EPD_Full(WHITE);              // Fill the entire canvas with white.
    //EPD_ShowPicture(0, 0, 400, 300, gImage_1, BLACK);
    //EPD_Display_Fast(Image_BW);
    
    imageBuffer = (uint8_t*)ps_malloc(IMAGE_SIZE);
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    client.setBufferSize(16000); 
}



void loop() {
  if (!client.connected()) {
    client.connect("epaper_display");
    client.subscribe("epaper/image");
  }
  client.loop();
}

