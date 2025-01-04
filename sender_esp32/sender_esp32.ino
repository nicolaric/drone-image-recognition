#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

uint8_t broadcastAddresses[][6] = {
  { 0x88, 0x13, 0xbf, 0x0d, 0x8f, 0x68 },
};

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// sender mac: 2c:bc:bb:4c:6a:30
// receiver mac: 88:13:bf:0d:8f:68

void setup(){
  Serial.begin(1000000);

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg);
  esp_wifi_set_mode(WIFI_MODE_STA);
  esp_wifi_set_bandwidth(WIFI_IF_STA, WIFI_BW_HT20);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);
  esp_wifi_set_ps(WIFI_PS_NONE);

  esp_wifi_start();

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddresses[0], 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

char buffer[1024]; 
void loop(){
  int availableBytes = Serial.available();
  if (availableBytes) {
    //int droneIndex = Serial.read() - '0';
    buffer[0] = 'H';
    buffer[1] = 'e';
    buffer[2] = 'l';
    buffer[3] = 'l';
    buffer[4] = 'o';
    buffer[5] = '\0';
    Serial.printf("\n drone index %d: ", 0);
    Serial.print(buffer);

    esp_err_t result = esp_now_send(broadcastAddresses[0], (uint8_t *)&buffer, strlen(buffer) + 1);
    if (result) {
        Serial.println(esp_err_to_name(result));
    }
  } else {
    Serial.print("no bytes available");
    yield();
  }
}
