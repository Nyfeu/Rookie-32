#ifndef _BLUETOOTH_HANDLER_HPP
#define _BLUETOOTH_HANDLER_HPP

#include <Arduino.h>
#include <BluetoothSerial.h>
#include "Emotion.hpp"
#include "Aplic.hpp"

class BluetoothHandler {

    public:
    
        BluetoothHandler();

        void begin(const String& deviceName = "ESP32_BT");
        void handleClient();

        // Callbacks para executar sons
        void setSoundCallback(void (*cb)(Emotion)) {
            soundCallback = cb;
        }

    private:

        // Serial Bluetooth
        BluetoothSerial _btSerial;

        // Callback para executar sons
        void (*soundCallback)(Emotion);

        // Callbacks que você pode sobrescrever se quiser
        void onMoveCommand(const String& cmd);
        void onSoundCommand(const String& cmd);
        void onUnknownCommand(const String& cmd);
        void onBatteryCommand();

        // Funções auxiliares
        float extractParam(const String& input, const String& key);
        Emotion getEmotionFromString(const String& emotionStr);

};

#endif /* _BLUETOOTH_HANDLER_HPP */
