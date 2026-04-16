#include <EspNowDev.h>

EspNowDev node;

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void setup(){
    Serial.begin(9600);

    if (!node.begin("SECRET_KEY_123")){
        Serial.println("Failed to initialize the protocol!");
        return;
    }

    Serial.println("Node ready. Waiting for data...");

    node.onMessageReceived([] (DataPacket packet){
        Serial.println("--- Data Received ---");
        Serial.print("Sender ID: "); Serial.println(packet.id);
        Serial.print("Sensor Value: "); Serial.println(packet.value);
        Serial.println("---------------------");
    });
}

void loop(){
    DataPacket myData;
    myData.id = 101;
    myData.value = random(20, 40);

    Serial.print("Sending data: "); Serial.println(myData.value);
    node.sendData(broadcastAddress, myData);

    delay(5000);
}