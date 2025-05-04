#include "Modules/WiFi_AP.hpp"

// Inicializa o Access Point e configura os endpoints do servidor
void WiFi_AP::begin() {

    // Configuração do IP fixo do AP (Gateway)
    IPAddress local_IP(192, 168, 4, 1);
    IPAddress gateway(192, 168, 4, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig(local_IP, gateway, subnet);

    // Cria um ponto de acesso com o SSID e senha definidos
    WiFi.softAP(ssid, password);

    // Obtém o IP do Access Point
    IPAddress IP = WiFi.softAPIP();
    Serial.println("Access Point: [OK]");
    Serial.print("Endereço IP: [");
    Serial.print(IP);
    Serial.println("]");

    // Define o intervalo DHCP para liberar apenas 192.168.4.3 (dispositivo móvel)
    tcpip_adapter_dhcps_lease_t lease;
    lease.enable = true;
    IP4_ADDR(&lease.start_ip, 192, 168, 4, 3);
    IP4_ADDR(&lease.end_ip, 192, 168, 4, 3);
    tcpip_adapter_dhcps_option(
        TCPIP_ADAPTER_OP_SET,
        TCPIP_ADAPTER_REQUESTED_IP_ADDRESS,
        &lease,
        sizeof(lease)
    );

    // Define a função que será chamada quando um cliente se conectar ou desconectar
    WiFi.onEvent(std::bind(&WiFi_AP::handleClientConnection, this, std::placeholders::_1));

    // Define os endpoints do servidor web local
    server.on("/move", [this]() { this->handleMove(); });      // Endpoint para movimento
    server.on("/sound", [this]() { this->handleSound(); });    // Endpoint para som/emotion
    server.onNotFound([this]() { this->handleNotFound(); });   // Tratamento para endpoints inexistentes

    // Inicia o servidor
    server.begin();

}

// Trata requisições para o endpoint /move
void WiFi_AP::handleMove() {

    // Verifica se os parâmetros "x" e "y" foram recebidos
    if (server.hasArg("x") && server.hasArg("y")) {

        String x = server.arg("x");
        String y = server.arg("y");

        // Imprime os valores recebidos via Serial
        Serial.printf("Received X: %s, Y: %s\n", x.c_str(), y.c_str());

        // Retorna sucesso para o cliente
        server.send(200, "text/plain", "Coordinates received");

    } else {

        // Parâmetros ausentes
        server.send(400, "text/plain", "Missing x or y parameter");

    }

}

// Trata requisições para o endpoint /sound
void WiFi_AP::handleSound() {

    // Verifica se o parâmetro "name" foi recebido
    if (server.hasArg("name")) {

        String name = server.arg("name");

        // Imprime o nome do som recebido
        Serial.printf("SOUND NAME: [%s]\n", name.c_str());
        server.send(200, "text/plain", "SOUND NAME RECEIVED: [OK]");

        // Converte o nome do som em uma emoção
        Emotion emotion = getEmotionFromString(name);

        if (emotion != ERROR) {

            // Executa a callback com a emoção correspondente
            soundCallback(emotion);

        }
    

    } else {

        // Parâmetro ausente
        server.send(400, "text/plain", "MISSING SOUND 'name' PARAMETER");

    }

}

// Trata requisições para endpoints inexistentes
void WiFi_AP::handleNotFound() {

    server.send(404, "text/plain", "Endpoint not found");

}

// Trata eventos de conexão e desconexão de clientes no Access Point
void WiFi_AP::handleClientConnection(WiFiEvent_t event) {

    if (event == ARDUINO_EVENT_WIFI_AP_STACONNECTED) {

        // Quando o cliente se CONECTA

        Serial.println("WIFI CLIENT: [CONNECTED]");
        if (onConnectionCallback) onConnectionCallback();
        else  Serial.println("Nenhuma callback configurada");

    } else if (event == ARDUINO_EVENT_WIFI_AP_STADISCONNECTED) {

        // Quando o cliente se DESCONECTA

        Serial.println("WIFI CLIENT: [DISCONNECTED]");
        if (onDisconnectionCallback) onDisconnectionCallback();
        else  Serial.println("Nenhuma callback configurada");

    }
    
}

// Converte uma string recebida para o tipo de emoção correspondente
Emotion WiFi_AP::getEmotionFromString(const String& emotionStr) {
            
    if (emotionStr.equalsIgnoreCase("happiness")) return HAPPINESS;
    if (emotionStr.equalsIgnoreCase("sadness")) return SADNESS;
    if (emotionStr.equalsIgnoreCase("anxiety")) return ANXIETY;
    if (emotionStr.equalsIgnoreCase("confusion")) return CONFUSION;
    if (emotionStr.equalsIgnoreCase("calm")) return CALM;
    if (emotionStr.equalsIgnoreCase("alert")) return ALERT;
    
    return ERROR; // Retorna erro caso a emoção não seja reconhecida

}

