#ifndef _UART_HANDLER_HPP
#define _UART_HANDLER_HPP

#include <Arduino.h>
#include <HardwareSerial.h>
#include "Emotion.hpp"

class UartHandler {

    public:
    
        UartHandler(HardwareSerial& serial, int rxPin, int txPin, unsigned long baud = 9600);

        void begin();
        void handleClient();

        // Callbacks para executar sons
        void setSoundCallback(void (*cb)(Emotion)) {
            soundCallback = cb;
        }

        // Callbacks que você pode sobrescrever se quiser
        void onMoveCommand(const String& cmd);
        void onSoundCommand(const String& cmd);
        void onUnknownCommand(const String& cmd);

    private:

        void (*soundCallback)(Emotion);

        HardwareSerial& _serial;

        int _rxPin;
        int _txPin;

        unsigned long _baud;

        float extractParam(const String& input, const String& key);
        Emotion getEmotionFromString(const String& emotionStr);

};

#endif /* _UART_HANDLER_HPP */
