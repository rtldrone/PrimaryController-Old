#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <Wire.h>

#include "Constants.h"
#include "HMIWebserver.h"
#include "FaultManager.h"
#include "VescCommManager.h"

#define I2C_ENABLE_BYTE 0b01010101

void sendSafetyUpdate() {
    Wire.beginTransmission(8);
    Wire.write(I2C_ENABLE_BYTE);
    Wire.endTransmission();
}

void setup() {
#ifdef DO_DEBUG
    Serial.begin(115200); //Only enable USB serial if debugging is enabled
#endif
    VESC_SERIAL_INTERFACE.begin(VESC_SERIAL_BAUDRATE);
    Wire.setClock(WIRE_CLOCK);
    Wire.begin();
    SPIFFS.begin();
    WiFi.mode(WIFI_AP);
    auto ip = IPAddress(SOFT_AP_IP);
    auto subnet = IPAddress(SOFT_AP_SUBNET_MASK);
    WiFi.softAPConfig(ip, ip, subnet);
    WiFi.softAP(SOFT_AP_SSID);

    VescCommManager::begin(&Serial2);
    HMIWebserver::begin();
}

void loop() {
    //vTaskDelete(nullptr); //Cancel the loop task as we aren't using it
    sendSafetyUpdate();
    delay(100);
}