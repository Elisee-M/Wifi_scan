#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(0);
  wifi_set_promiscuous_rx_cb(snifferCallback);
  wifi_promiscuous_enable(1);
  Serial.println("🚀 Sniffing started...");
}

void loop() {
  // Nothing here
}

void snifferCallback(uint8_t *buf, uint16_t len) {
  if (len == 12) return;

  uint8_t* mac = buf + 10;
  int rssi = -(buf[0x22]);
  Serial.print("📡 MAC: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", mac[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.print(" | RSSI: ");
  Serial.println(rssi);
}
