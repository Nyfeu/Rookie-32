#include "Modules/WiFi_AP.hpp"

// Inicializa o Access Point e configura os endpoints do servidor
void WiFi_AP::begin() {

    // Configurações de rede estática
    IPAddress staticIP(192, 168, 4, 2);     // IP do cliente
    IPAddress gateway(192, 168, 4, 1);      // IP do AP (Gateway)
    IPAddress subnet(255, 255, 255, 0);     // Máscara de rede

    // Configura IP estático antes de conectar
    WiFi.config(staticIP, gateway, subnet);

    Serial.println();
    Serial.print("Conectando a: [");
    Serial.print(ssid);
    Serial.println("]");

    WiFi.begin(ssid, password);

    // Aguarda conexão
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // Exibe informações da conexão
    Serial.println("\nConection: [OK]");
    Serial.print("IP estático: [");
    Serial.print(WiFi.localIP());
    Serial.println("]");

    // Endpoints reais
    controlServer.on("/move", [this]() { handleMove(); });
    controlServer.on("/sound", [this]() { handleSound(); });

    // Inicializa o servidor de controle
    controlServer.begin();
    
    // Exibe informações do servidor
    Serial.println("Control Server: [OK]");
    Serial.print("IP: [");
    Serial.print(WiFi.localIP());
    Serial.println("]");

}

// Trata requisições para o endpoint /move
void WiFi_AP::handleMove() {

    // Verifica se os parâmetros "x" e "y" foram recebidos
    if (controlServer.hasArg("x") && controlServer.hasArg("y")) {

        String x = controlServer.arg("x");
        String y = controlServer.arg("y");

        // Imprime os valores recebidos via Serial
        Serial.printf("Received X: %s, Y: %s\n", x.c_str(), y.c_str());

        // Retorna sucesso para o cliente
        controlServer.send(200, "text/plain", "Coordinates received");

    } else {

        // Parâmetros ausentes
        controlServer.send(400, "text/plain", "Missing x or y parameter");

    }

}

// Trata requisições para o endpoint /sound
void WiFi_AP::handleSound() {

    // Verifica se o parâmetro "name" foi recebido
    if (controlServer.hasArg("name")) {

        String name = controlServer.arg("name");

        // Imprime o nome do som recebido
        Serial.printf("SOUND NAME: [%s]\n", name.c_str());
        controlServer.send(200, "text/plain", "SOUND NAME RECEIVED: [OK]");

        // Converte o nome do som em uma emoção
        Emotion emotion = getEmotionFromString(name);

        if (emotion != ERROR) {

            // Executa a callback com a emoção correspondente
            soundCallback(emotion);

        }

        String response = "{\"status\":\"success\",\"sound\":\"" + name + "\"}";
        controlServer.send(200, "application/json", response);

    } else {

        // Parâmetro ausente
        controlServer.send(400, "text/plain", "MISSING SOUND 'name' PARAMETER");

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

