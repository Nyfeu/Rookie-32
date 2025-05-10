#include "Modules/UARTHandler.hpp"

UartHandler::UartHandler(HardwareSerial& serial, int rxPin, int txPin, unsigned long baud)
    : _serial(serial), _rxPin(rxPin), _txPin(txPin), _baud(baud) {}

void UartHandler::begin() {

    _serial.begin(_baud, SERIAL_8N1, _rxPin, _txPin);
    Serial.println("UART Handler: [OK]");

}

void UartHandler::handleClient() {

    if (_serial.available()) {

        String command = _serial.readStringUntil('\n');
        command.trim();

        Serial.print("Recebido via UART: ");
        Serial.println(command);

        if (command.startsWith("/move?")) onMoveCommand(command);
        else if (command.startsWith("/sound?")) onSoundCommand(command);
        else onUnknownCommand(command);
        
    }

}

// Trata comandos do tipo /move?x=...&y=...
void UartHandler::onMoveCommand(const String& cmd) {

    float x = extractParam(cmd, "x");
    float y = extractParam(cmd, "y");

    Serial.print("Comando MOVE → x = ");
    Serial.print(x);
    Serial.print(", y = ");
    Serial.println(y);

}

// Trata comandos do tipo /sound?name=...
void UartHandler::onSoundCommand(const String& cmd) {

    String name = cmd.substring(cmd.indexOf('=') + 1);

    if (name.length() > 0) {

        Serial.print("Comando SOUND → name = ");
        Serial.println(name);

        Emotion emotion = getEmotionFromString(name);
        if (emotion != ERROR) {
            soundCallback(emotion);
        }

    } else {

        Serial.println("Parâmetro 'name' ausente");
    
    }

}

void UartHandler::onUnknownCommand(const String& cmd) {

    Serial.println("Comando desconhecido:");
    Serial.println(cmd);

}

// Extrai valor de parâmetro da query (ex: "x=10&y=20")
float UartHandler::extractParam(const String& input, const String& key) {
    
    int keyIndex = input.indexOf(key + "=");
    if (keyIndex == -1) return 0.0;

    int start = keyIndex + key.length() + 1;
    int end = input.indexOf('&', start);
    if (end == -1) end = input.length();

    String valueStr = input.substring(start, end);
    return valueStr.toFloat();

}

// Converte uma string recebida para o tipo de emoção correspondente
Emotion UartHandler::getEmotionFromString(const String& emotionStr) {
            
    if (emotionStr.equalsIgnoreCase("happiness")) return HAPPINESS;
    if (emotionStr.equalsIgnoreCase("sadness")) return SADNESS;
    if (emotionStr.equalsIgnoreCase("anxiety")) return ANXIETY;
    if (emotionStr.equalsIgnoreCase("confusion")) return CONFUSION;
    if (emotionStr.equalsIgnoreCase("calm")) return CALM;
    if (emotionStr.equalsIgnoreCase("alert")) return ALERT;
    
    return ERROR; // Retorna erro caso a emoção não seja reconhecida

}