#ifndef ESP_NOW_DEV_H
#define ESP_NOW_DEV_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <functional> // callback

struct DataPacket { int id; float value; };

class EspNowDev {
public:
    EspNowDev();
    bool begin(const char* secretKey = nullptr);
    void sendData(const uint8_t* peerAddr, DataPacket data);
    // Lambda
    void onMessageReceived(std::function<void(DataPacket)> callback);

private:
    static std::function<void(DataPacket)> _onReceiveCallback;
    static void _internalMsgHandler(const uint8_t* mac, const uint8_t* incomingData, int len)
};

#endif

