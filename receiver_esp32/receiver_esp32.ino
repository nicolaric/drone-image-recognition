#include <WiFi.h>
#include <esp_now.h>

void OnDataReceived(const esp_now_recv_info* info, const uint8_t* data, int len) {
  //Serial.println("Received data from MAC address");
  //for (int i = 0; i < 6; i++) {
    //Serial.printf("%02X:", info->mac[i]);
  //}
  //Serial.println();

  // Process received data here
  Serial.print("Data: ");
  for (int i = 0; i < len; i++) {
    Serial.print((char)data[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void setup() {
  Serial.begin(1000000);
  WiFi.mode(WIFI_STA);  // Set WiFi mode to Station
  esp_now_init();  // Initialize ESP-NOW
  
  // Register the receive callback function with the correct signature
  esp_now_register_recv_cb(OnDataReceived);
}

void loop() {
  // Your main loop code here
}

