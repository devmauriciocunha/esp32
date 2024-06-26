# Localizador de Objetos com BLE e MQTT 🌐💬

## Sobre 📘
Esse projeto transforma o ESP32 visa ser capaz de identificar dispositivos BLE (Bluetooth Low Energy) nas proximidades e calcular a distância até eles com o calculo RSSI. As informações são enviadas via MQTT, mantendo você sempre informado.

## Materiais Necessários 🛠️
- ESP32
- Acesso a um servidor MQTT

## Bibliotecas Requeridas 📚
- WiFi.h
- PubSubClient.h
- BLEDevice.h
- BLEUtils.h
- BLEServer.h
- BLEScan.h

## Configurações Iniciais 🔧
Configurar é simples:
1. Defina as credenciais do Wi-Fi e o servidor MQTT.
2. Carregue o código no ESP32 e pronto para a mágica acontecer!

## Como Funciona 🚀
- **Conexão Wi-Fi:** Conecta-se à sua rede Wi-Fi favorita.
- **Cliente MQTT:** Envia os dados dos dispositivos BLE detectados para o servidor.
- **BLE Scanning:** Regularmente procura por gadgets BLE nas redondezas e calcula quão perto eles estão.

## Pronto para a Ação! 🎉
Sente-se e observe enquanto seu ESP32 faz todo o trabalho pesado de monitoramento BLE, mantendo você atualizado através do MQTT.
