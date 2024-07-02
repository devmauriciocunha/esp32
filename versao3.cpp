#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Mauricio"; // Replace with your Wi-Fi network SSID
const char* password = "MNC123456"; // Replace with your Wi-Fi network password
const char* mqtt_server = "172.20.10.10"; // Replace with your MQTT server address
const int mqtt_port = 1883;
const char* mqtt_topic = "mauricio/msg"; // Replace with your desired MQTT topic

WiFiClient espClient;
PubSubClient mqttClient(espClient);

int rssi;
String deviceName = "";

// Reference RSSI value (adjust based on environment)
const int RSSI0_INDOOR = -59; // Typical indoor value
const int RSSI0_OUTDOOR = -70; // Typical outdoor value

// Path loss exponent (adjust based on environment)
const float n_INDOOR = 3.0f; // Typical indoor value
const float n_OUTDOOR = 3.5f; // Typical outdoor value

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!mqttClient.connected()) {
    if (mqttClient.connect("ESP32Client")) {
      // Subscribe to a topic potentially containing device names (modify as needed)
      mqttClient.subscribe("devices/names"); 
    } else {
      delay(5000);
    }
  }
}

void onMessage(char* topic, byte* payload, unsigned int length) {
  // Check if received message is on the subscribed topic (modify as needed)
  if (strcmp(topic, "devices/names") == 0) {
    deviceName = String((char*)payload); // Update device name
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(onMessage); // Set callback for incoming messages
  reconnect();
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  rssi = WiFi.RSSI();  // Get RSSI value

  // Determine indoor or outdoor environment (modify based on your logic)
  bool isIndoor = true; // Assuming indoor environment by default

  // Calculate estimated distance in meters
  float distance_m = 10.0f * ((float)rssi - (float)(isIndoor ? RSSI0_INDOOR : RSSI0_OUTDOOR)) / (float)(isIndoor ? n_INDOOR : n_OUTDOOR);

  // Convert distance to centimeters
  float distance_cm = distance_m * 100.0f;

  // Prepare message with device name (if available), RSSI, and estimated distance
  String message = "";
  if (deviceName.length() > 0) {
    message += deviceName;
    message += " (";
  }
  message += String(rssi);
  message += " dBm, ";
  message += String(distance_m, 1); // Format distance to one decimal place
  message += " m, ";
  message += String(distance_cm, 1); // Format distance to one decimal place
  message += " cm";
  if (deviceName.length() > 0) {
    message += ")";
  }

  // Publish message to the MQTT topic
  mqttClient.publish(mqtt_topic, message.c_str());

  delay(2000);
}
