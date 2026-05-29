#include <Arduino.h>

int readBatteryPercent() {
    analogReadResolution(12);
    analogSetAttenuation(ADC_11db);

    int raw = analogRead(8);
    float vPin  = (raw / 4095.0f) * 3.1f;
    float vBat = vPin * 2.0f * 1.27f;
    float pct   = (vBat - 3.0f) / (4.2f - 3.0f) * 100.0f;
    if (pct > 100.0f) pct = 100.0f;
    if (pct <   0.0f) pct =   0.0f;
    return (int)pct;
}