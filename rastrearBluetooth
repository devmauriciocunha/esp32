#include <WiFi.h>
#include <PubSubClient.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEScan.h>

const char* ssid = "Mauricio";
const char* password = "MNC123456";
const char* mqtt_server = "172.20.10.5";
// Dados da rede Wi-Fi e MQTT
//const char* ssid = "NET_2GE9D15E";
//const char* password = "MNC32282633";
//const char* mqtt_server = "192.168.0.3";
const int mqtt_port = 1883;
const char* mqtt_topic = "mauricio/ble_data";

// Dados de BLE
const float max_distance = 10.0;
const float RSSI_0 = -59;
const float ENVIRONMENTAL_FACTOR_N = 2;

WiFiClient espClient;
PubSubClient mqttClient(espClient);
BLEServer* pBLEServer;
BLEService* pBLEService;
BLEScan* pBLEScan;

// Classe para lidar com eventos de conexão e desconexão
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) override {
        Serial.println("Dispositivo BLE conectado");
    }

    void onDisconnect(BLEServer* pServer) override {
        Serial.println("Dispositivo BLE desconectado");
    }
};

// Função para calcular a distância com base no RSSI
float calculateDistance(int rssi) {
  return pow(10, (RSSI_0 - rssi) / (10 * ENVIRONMENTAL_FACTOR_N));
}

void setup_wifi() {
  Serial.begin(115200);
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: " + WiFi.localIP().toString());
}

void reconnect_mqtt() {
  while (!mqttClient.connected()) {
    Serial.println("Conectando ao servidor MQTT...");
    if (mqttClient.connect("ESP32_BLE_MQTT_Client")) {
      Serial.println("Conectado ao servidor MQTT");
    } else {
      Serial.print("Falha ao conectar ao MQTT: ");
      Serial.println(mqttClient.state());
      delay(5000);
    }
  }
}

void setup_ble() {
  BLEDevice::init("ESP32_BLE_Test");
  pBLEServer = BLEDevice::createServer();
  pBLEServer->setCallbacks(new MyServerCallbacks()); // Configura as callbacks
  pBLEService = pBLEServer->createService(BLEUUID((uint16_t)0xFFE0));
  pBLEService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(pBLEService->getUUID());
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  pAdvertising->start();

  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}

void scanBLEDevices() {
  BLEScanResults foundDevices = pBLEScan->start(5, false);
  String message = "Dispositivos Detectados: ";
  int deviceCount = 0;

  for (int i = 0; i < foundDevices.getCount(); i++) {
    BLEAdvertisedDevice device = foundDevices.getDevice(i);
    float distanceMeters = calculateDistance(device.getRSSI());
    
    if (distanceMeters <= max_distance) {
      deviceCount++;
      String deviceAddress = String(device.getAddress().toString().c_str());
      message += "Dispositivo " + String(deviceCount) + ": " + 
                 deviceAddress + ", RSSI: " + String(device.getRSSI()) + 
                 ", Distância: " + String(distanceMeters, 2) + "m / " + 
                 String(distanceMeters * 100, 0) + "cm; ";
    }
  }

  message = "Total de Dispositivos dentro de " + String(max_distance) + "m: " + 
            String(deviceCount) + "; " + message;
  mqttClient.publish(mqtt_topic, message.c_str());
  pBLEScan->clearResults();
}

void setup() {
  setup_wifi();
  mqttClient.setServer(mqtt_server, mqtt_port);
  reconnect_mqtt();
  setup_ble();
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect_mqtt();
  }
  mqttClient.loop();
  scanBLEDevices();
  delay(5000);
}
