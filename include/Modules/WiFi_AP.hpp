#ifndef WIFI_AP_HPP
#define WIFI_AP_HPP

#include <WiFi.h>
#include <WebServer.h>
#include <functional>
#include "Emotion.hpp"

class WiFi_AP {

    public:

        WiFi_AP(const char* ssid, const char* password)
            : ssid(ssid), password(password), server(80), onConnectionCallback(nullptr), onDisconnectionCallback(nullptr) {}

        void begin();

        void handleClient() {
            server.handleClient();
        }

        void setClientConnectCallback(void (*cb)()) {
            onConnectionCallback = cb;
        }

        void setClientDisconnectCallback(void (*cb)()) {
            onDisconnectionCallback = cb;
        }

        void setSoundCallback(void (*cb)(Emotion)) {
            soundCallback = cb;
        }

    private:

        WebServer server;
        
        const char* ssid;
        const char* password;
        
        void (*onConnectionCallback)();
        void (*onDisconnectionCallback)();
        void (*soundCallback)(Emotion);

        void handleMove();

        void handleSound();

        void handleNotFound();
        
        // Callback que será chamada quando um cliente se conectar
        void handleClientConnection(WiFiEvent_t event);

        // Converte string para enum
        Emotion getEmotionFromString(const String& emotionStr);

};

#endif /* WIFI_AP_HPP */
