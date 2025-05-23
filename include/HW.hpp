#ifndef _HW_H
#define _HW_H

#include "Aplic.hpp"
#include "Modules/Beeper.hpp"
#include "Modules/BatteryMonitor.hpp"
#include "Modules/ObstacleDetector.hpp"
#include "Modules/MotorController.hpp"

// Instância do beeper utilizando o pino do buzzer
Beeper beeper(BUZZER_PIN);

// Instância do controle de motores
MotorController motor(MOTOR_IN1A, MOTOR_IN1B, MOTOR_IN2A, MOTOR_IN2B);

// Instância de monitor de bateria
BatteryMonitor battery(BATT_PIN);

/**
 * @brief Inicializa o PWM para o buzzer.
 * Configura o canal PWM no pino BUZZER_PIN com 1kHz e 8 bits de resolução.
 * Define o duty cycle inicial para 50%.
 */
void initBuzzerPWM() {

    ledcSetup(BUZZER_CHANNEL, 1000, 8); // Frequência de 1kHz, resolução de 8 bits
    ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
    ledcWrite(BUZZER_CHANNEL, 128); // Duty cycle de 50% (valor entre 0-255)

}

/**
 * @brief Inicializa o PWM para os motores (implementação futura).
 * Essa função será utilizada para configurar os canais PWM dos motores.
 */
void initMotor() {
    // Configuração para os motores 
    motor.begin();
    motor.pararTodos(); // Para todos os motores
}

/**
 * @brief Inicializa a comunicação serial.
 * Configura a Serial Monitor com a taxa de transmissão definida e aguarda conexão.
 * Após a inicialização, imprime mensagens indicando status e toca um som de felicidade.
 */
void initSerialComms() {

    Serial.begin(BAUD_RATE);
    while (!Serial); // Aguarda inicialização da Serial
    delay(1000); // Pequeno atraso para garantir a estabilização
    Serial.println("Serial Monitor: [OK]");

}

/**
 * @brief Configura os parâmetros do monitor de bateria.
 */
void initBatteryADC() {

    analogReadResolution(12); 
    battery.setMaxBatteryVoltage(MAX_BATTERY_VOLTAGE); // Tensão máxima da bateria
    battery.setMinBatteryVoltage(MIN_BATTERY_VOLTAGE); // Tensão mínima da bateria

}

/**
 * @brief Configura os pinos de entrada e saída do hardware.
 * Define os modos dos pinos utilizados no projeto.
 */
void initPinout() {
    
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    
}

/**
 * @brief Inicializa todo o hardware do sistema.
 * Chama as funções de configuração de PWM, pinos e comunicação serial.
 * Exibe mensagem indicando sucesso na inicialização do hardware.
 */
void initHW() {

    initBuzzerPWM();
    initMotor();
    initBatteryADC();
    initPinout();
    initSerialComms();

    Serial.println("Hardware Initialization: [OK]");
    
}

#endif /* _HW_H */
