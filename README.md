# Projeto ESP32 com BLE e MQTT

## Descrição
Este projeto permite que um ESP32 detecte dispositivos BLE (Bluetooth Low Energy) próximos, calcule a distância até esses dispositivos com base no RSSI e envie essas informações via MQTT.

## Componentes
- ESP32
- Servidor MQTT

## Bibliotecas Necessárias
- WiFi.h
- PubSubClient.h
- BLEDevice.h
- BLEUtils.h
- BLEServer.h
- BLEScan.h

## Configuração
1. Configure as credenciais do WiFi e o endereço do servidor MQTT no início do código.
2. Compile e faça o upload do código para o ESP32.

## Funcionalidade
- **Conexão Wi-Fi:** O ESP32 se conecta à rede Wi-Fi especificada.
- **Cliente MQTT:** Conecta-se a um servidor MQTT e envia dados coletados.
- **BLE Scanning:** Inicia o BLE para escanear dispositivos próximos e calcular a distância com base no RSSI.

## Uso
O dispositivo ESP32 periodicamente verifica a presença de dispositivos BLE dentro de um alcance definido e publica os detalhes (incluindo RSSI e distância calculada) para um tópico MQTT específico.
