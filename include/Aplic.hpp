/**
 * @file Aplic.hpp
 * @brief Definições globais de configuração e pinagem para o projeto Rookie-32.
 *
 * Este arquivo contém todas as definições importantes de macros para o projeto,
 * incluindo inclusões de bibliotecas principais (FreeRTOS e Arduino Framework),
 * configurações gerais, parâmetros da bateria, configurações do Watchdog Timer (WDT),
 * flags de debug, pinagem de hardware, configurações de comunicação serial,
 * e parâmetros para o sensor de obstáculos e comunicação Wi-Fi.
 */

#ifndef APLIC_HPP
#define APLIC_HPP

//-----------------------------------------------------------------------------------------------------------
//   Inclusões Principais (FreeRTOS & Arduino Framework)

#include "Arduino.h"                        // Framework do Arduino
#include <freertos/FreeRTOS.h>              // Núcleo do FreeRTOS: permite gerenciamento de tarefas no ESP32
#include <freertos/task.h>                  // Manipulação de tarefas (tasks) no FreeRTOS
#include <freertos/semphr.h>                // Gerenciamento de semáforos no FreeRTOS
#include <esp_task_wdt.h>                   // Biblioteca do ESP32 para configurar e interagir com o Watchdog Timer

//-----------------------------------------------------------------------------------------------------------
//   Gerais

/** @defgroup General_Configs Configurações Gerais
 * @{
 */

/**
 * @brief Macro para habilitar uma funcionalidade (valor 1).
 */
#define ON                   1

/**
 * @brief Macro para desabilitar uma funcionalidade (valor 0).
 */
#define OFF                  0

/** @} */ // Fim do grupo General_Configs

//-----------------------------------------------------------------------------------------------------------
//   Bateria

/** @defgroup Battery_Configs Configurações da Bateria
 * @{
 */

/**
 * @brief Tensão máxima esperada da bateria (valor lido no pino ADC) para 100% de carga.
 * @details Este valor é calibrado para corresponder a 8.0V na bateria real,
 * considerando um divisor de tensão para limitar a entrada do ADC a 3.0V.
 */
#define MAX_BATTERY_VOLTAGE  2.857          // 2.857V = 100% de carga (8.0V na bateria)

/**
 * @brief Tensão mínima esperada da bateria (valor lido no pino ADC) para 0% de carga.
 * @details Este valor é calibrado para corresponder a 6.0V na bateria real,
 * considerando um divisor de tensão.
 */
#define MIN_BATTERY_VOLTAGE  2.143          // 2.143V = 0.0% de carga (6.0V na bateria)

// Está sendo considerado um divisor de tensão, para limitar a tensão de entrada do ADC a 3.0V
// Um limiar (threshold) é definido a partir de 8.0V na bateria - para 100% da carga

/** @} */ // Fim do grupo Battery_Configs

//------------------------------------------------------------------------------
//   Watchdog Timer (WDT)

/** @defgroup WDT_Configs Configurações do Watchdog Timer (WDT)
 * @{
 */

/**
 * @brief Ativa ou desativa o Task Watchdog Timer (TWDT) do sistema.
 * @details Use ON para ativar e OFF para desativar.
 */
#define WDT_ACTIVE  OFF                     ///< ON/OFF o WDT do sistema

/**
 * @brief Tempo limite do Watchdog Timer (WDT) em segundos.
 * @details Se uma tarefa não "alimentar" o WDT dentro deste tempo, o sistema será reiniciado.
 */
#define WDT_TIMEOUT  5                      ///< Timeout Watchdog Timer (WDT) [s]

/** @} */ // Fim do grupo WDT_Configs

//-----------------------------------------------------------------------------------------------------------
//   Debug

/** @defgroup Debug_Flags Flags de Debug
 * @{
 */

 /**
 * @brief Habilita a verificação da inicialização dos Task Watchdog Timers (TWDTs).
 * @details Use ON para habilitar a impressão do status de inicialização de cada TWDT no Serial Monitor.
 */
#define WDT_CHECK       OFF                 ///< Verifica inicialização dos TWDTs

/**
 * @brief Habilita mensagens de debug relacionadas ao controle dos motores.
 * @details Use ON para ver logs de movimentação dos motores no Serial Monitor.
 */
#define DEBUG_MOTORS    OFF                 ///< Verifica motores

/**
 * @brief Habilita mensagens de debug relacionadas ao beeper (buzzer).
 * @details Use ON para ver logs de ativação do buzzer no Serial Monitor.
 */
#define DEBUG_BEEPER    OFF                 ///< Verifica o buzzer

/**
 * @brief Habilita mensagens de debug relacionadas à detecção de obstáculos.
 * @details Use ON para ver logs de detecção de obstáculos no Serial Monitor.
 */
#define DEBUG_OBSTACLE  OFF                 ///< Verifica sensor de distância

/**
 * @brief Habilita a impressão da distância lida pelo sensor de obstáculos no Serial Monitor.
 * @details Use ON para ver o valor da distância lida.
 */
#define DEBUG_DISTANCE  OFF                 ///< Verifica distância lida pelo sensor

/**
 * @brief Habilita a impressão do nível de tensão e porcentagem da bateria no Serial Monitor.
 * @details Use ON para monitorar a bateria.
 */
#define DEBUG_VOLTAGE   OFF                 ///< Verifica nível de bateria

/**
 * @brief Habilita mensagens de debug relacionadas à comunicação serial (geral).
 * @details Use ON para ver dados de comunicação via Bluetooth e outras interações seriais.
 */
#define DEBUG_SERIAL    OFF                 ///< Verifica comunicação serial

/** @} */ // Fim do grupo Debug_Flags

//-----------------------------------------------------------------------------------------------------------
//   Pinout

/** @defgroup Pinout_Configs Configurações de Pinagem
 * @{
 */

/**
 * @brief Pino GPIO conectado ao pino TRIGGER do sensor ultrassônico HC-SR04.
 */
#define TRIGGER_PIN          33 

/**
 * @brief Pino GPIO conectado ao pino ECHO do sensor ultrassônico HC-SR04.
 */
#define ECHO_PIN             32 

/**
 * @brief Pino GPIO conectado ao buzzer.
 */
#define BUZZER_PIN           15 

/**
 * @brief Canal PWM utilizado para controlar o buzzer.
 */
#define BUZZER_CHANNEL       0  

/**
 * @brief Pino GPIO conectado ao divisor de tensão para leitura da bateria (ADC).
 */
#define BATT_PIN             34 

/**
 * @brief Pino do LED embutido na placa ESP32 (geralmente GPIO2).
 */
#define LED_BUILTIN          2

/**
 * @brief Pino GPIO para controle do IN1 do Motor A (Ponte H).
 */
#define MOTOR_IN1A          25

/**
 * @brief Pino GPIO para controle do IN2 do Motor A (Ponte H).
 */
#define MOTOR_IN2A          26

/**
 * @brief Pino GPIO para controle do IN1 do Motor B (Ponte H).
 */
#define MOTOR_IN1B          27

/**
 * @brief Pino GPIO para controle do IN2 do Motor B (Ponte H).
 */
#define MOTOR_IN2B          14

/** @} */ // Fim do grupo Pinout_Configs

//-----------------------------------------------------------------------------------------------------------
//   Comunicação Serial

/** @defgroup Serial_Comms_Configs Configurações de Comunicação Serial
 * @{
 */

/**
 * @brief Taxa de transmissão (baud rate) para a comunicação serial.
 */
#define BAUD_RATE 9600

/** @} */ // Fim do grupo Serial_Comms_Configs

//-----------------------------------------------------------------------------------------------------------
//   Obstáculos

/** @defgroup Obstacle_Detection_Configs Configurações de Detecção de Obstáculos
 * @{
 */

/**
 * @brief Distância mínima em centímetros para considerar a detecção de um obstáculo.
 */
#define MIN_DISTANCE 20

/** @} */ // Fim do grupo Obstacle_Detection_Configs

//-----------------------------------------------------------------------------------------------------------

#endif /* APLIC_HPP */