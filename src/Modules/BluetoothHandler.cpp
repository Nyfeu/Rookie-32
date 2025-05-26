#include "Modules/BluetoothHandler.hpp"
#include "Modules/MotorController.hpp"
#include "Modules/BatteryMonitor.hpp"

#if DEBUG_SERIAL == ON
    #define DEBUG_UNKNOWN_COMMAND(cmd) onUnknownCommand(cmd)
#else 
    #define DEBUG_UNKNOWN_COMMAND(cmd)
#endif

// Referência ao leitor de bateria (definido em HW.hpp)
extern BatteryMonitor battery;

// Referência ao controle dos motores (definido em HW.hpp)
extern MotorController motor;

// Inicialização do Serial Bluetooth
BluetoothHandler::BluetoothHandler() {}

void BluetoothHandler::begin(const String& deviceName) {
    _btSerial.begin(deviceName);
    Serial.println("Bluetooth Handler: [OK]");
}

// Inicia o Bluetooth e aguarda conexão
void BluetoothHandler::handleClient() {

    if (_btSerial.available()) {

        digitalWrite(LED_BUILTIN, HIGH);

        String command = _btSerial.readStringUntil('\n');
        command.trim();

        #if DEBUG_SERIAL == ON
            
            Serial.print("Recebido via Bluetooth: ");
            Serial.println(command);

        #endif

        if (command.startsWith("/move?")) onMoveCommand(command);
        else if (command.startsWith("/sound?")) onSoundCommand(command);
        else DEBUG_UNKNOWN_COMMAND(command);

        digitalWrite(LED_BUILTIN, LOW);

    }

}

// Trata comandos do tipo /move?x=...&y=...
void BluetoothHandler::onMoveCommand(const String& cmd) {

    float x = extractParam(cmd, "x");
    float y = extractParam(cmd, "y");

    motor.handle(x, y);

}

void BluetoothHandler::onBatteryCommand() {

    float voltage = battery.readBatteryVoltage();      
    float percentage = battery.getBatteryPercentage();

    _btSerial.print("BATTERY: ");
    _btSerial.printf("%.2fV (%.1f%%)\n", voltage, percentage);

    Serial.print("Respondendo nível da bateria: ");
    Serial.printf("%.2fV (%.1f%%)\n", voltage, percentage);

}


// Trata comandos do tipo /sound?name=...
void BluetoothHandler::onSoundCommand(const String& cmd) {

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

// Trata comandos desconhecidos
void BluetoothHandler::onUnknownCommand(const String& cmd) {

    Serial.println("Comando desconhecido:");
    Serial.println(cmd);

}

// Extrai valor de parâmetro da query (ex: "x=10&y=20")
float BluetoothHandler::extractParam(const String& input, const String& key) {
    
    int keyIndex = input.indexOf(key + "=");
    if (keyIndex == -1) return 0.0;

    int start = keyIndex + key.length() + 1;
    int end = input.indexOf('&', start);
    if (end == -1) end = input.length();

    String valueStr = input.substring(start, end);
    return valueStr.toFloat();

}

// Converte uma string recebida para o tipo de emoção correspondente
Emotion BluetoothHandler::getEmotionFromString(const String& emotionStr) {
            
    if (emotionStr.equalsIgnoreCase("happiness")) return HAPPINESS;
    if (emotionStr.equalsIgnoreCase("sadness")) return SADNESS;
    if (emotionStr.equalsIgnoreCase("anxiety")) return ANXIETY;
    if (emotionStr.equalsIgnoreCase("confusion")) return CONFUSION;
    if (emotionStr.equalsIgnoreCase("calm")) return CALM;
    if (emotionStr.equalsIgnoreCase("alert")) return ALERT;
    
    return ERROR; // Retorna erro caso a emoção não seja reconhecida

}