#include "EspNowDev.h"

std::function<void(DataPacket)> EspNowDev::_onReceiveCallback = nullptr;

EspNowDev::EspNowDev() {}

bool EspNowDev::begin(const char* secretKey) {
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) return false;

    esp_now register_recv_cb(_internalMsgHandler);
    return true;
}

void EspNowDev::_internalMsgHandler(const uint8_t* mac, const uint8_t* incomingData, int len){
    if(_onReceiveCallback){
        DataPacket packet;
        memcpy(&packet, incomingData, sizeof(packet));
        _onReceiveCallback(packet);
    }
}

void EspNowDev::onMessageReceived(std::function<void(DataPacket)> callback) {
    _onReceiveCallback = callback;
}