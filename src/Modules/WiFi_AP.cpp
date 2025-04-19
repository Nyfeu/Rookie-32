#include "Modules/WiFi_AP.hpp"

void WiFi_AP::begin() {

    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.println("Access Point: [OK]");
    Serial.print("Endereço IP: [");
    Serial.print(IP);
    Serial.println("]");

    WiFi.onEvent(std::bind(&WiFi_AP::handleClientConnection, this, std::placeholders::_1));

    server.on("/move", [this]() { this->handleMove(); });
    server.on("/sound", [this]() { this->handleSound(); });
    server.onNotFound([this]() { this->handleNotFound(); });

    server.begin();

}

void WiFi_AP::handleMove() {

    if (server.hasArg("x") && server.hasArg("y")) {

        String x = server.arg("x");
        String y = server.arg("y");

        Serial.printf("Received X: %s, Y: %s\n", x.c_str(), y.c_str());
        server.send(200, "text/plain", "Coordinates received");

    } else {

        server.send(400, "text/plain", "Missing x or y parameter");

    }

}

void WiFi_AP::handleSound() {

    if (server.hasArg("name")) {

        String name = server.arg("name");

        Serial.printf("SOUND NAME: [%s]\n", name.c_str());
        server.send(200, "text/plain", "SOUND NAME RECEIVED: [OK]");

        Emotion emotion = getEmotionFromString(name);

        if (emotion != ERROR) {

            soundCallback(emotion);
            
            /*xSemaphoreTake(emotionStateMutex, portMAX_DELAY);
            eyes.setEmotion(emotion);
            xSemaphoreGive(emotionStateMutex);*/

        }
    

    } else {

        server.send(400, "text/plain", "MISSING SOUND 'name' PARAMETER");

    }

}

void WiFi_AP::handleNotFound() {

    server.send(404, "text/plain", "Endpoint not found");

}

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

Emotion WiFi_AP::getEmotionFromString(const String& emotionStr) {
            
    if (emotionStr.equalsIgnoreCase("happiness")) return HAPPINESS;
    if (emotionStr.equalsIgnoreCase("sadness")) return SADNESS;
    if (emotionStr.equalsIgnoreCase("anxiety")) return ANXIETY;
    if (emotionStr.equalsIgnoreCase("confusion")) return CONFUSION;
    if (emotionStr.equalsIgnoreCase("calm")) return CALM;
    if (emotionStr.equalsIgnoreCase("alert")) return ALERT;
    
    return ERROR; 

}

