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

#define ON  1                               // Ativo (ON)
#define OFF 0                               // Inativo (OFF)

//-----------------------------------------------------------------------------------------------------------
//   Bateria

#define MAX_BATTERY_VOLTAGE  2.857          // 2.857V = 100% de carga (8.0V na bateria)
#define MIN_BATTERY_VOLTAGE  2.143          // 2.143V = 0.0% de carga (6.0V na bateria)

// Está sendo considerado um divisor de tensão, para limitar a tensão de entrada do ADC a 3.0V
// Um limiar (threshold) é definido a partir de 8.0V na bateria - para 100% da carga

//------------------------------------------------------------------------------
//   Watchdog Timer (WDT)

#define WDT_ACTIVE  OFF                     // ON/OFF o WDT do sistema
#define WDT_TIMEOUT  5                      // Timeout Watchdog Timer (WDT) [s]

//-----------------------------------------------------------------------------------------------------------
//   Debug

#define WDT_CHECK       ON                  // Verifica inicialização dos TWDTs
#define DEBUG_OBSTACLE  ON                  // Verifica sensor de distância
#define DEBUG_DISTANCE  OFF                 // Verifica distância lida pelo sensor
#define DEBUG_VOLTAGE   ON                  // Verifica nível de bateria

//-----------------------------------------------------------------------------------------------------------
//   Pinout

#define TRIGGER_PIN           2             // PIN_24 (GPIO_2 ) - Pino de trigger do sensor ultrassônico
#define ECHO_PIN             15             // PIN_23 (GPIO_15) - Pino de echo do sensor ultrassônico
#define BUZZER_PIN           18             // PIN_30 (GPIO_18) - Pino do buzzer (speaker)
#define BATT_PIN              4             // PIN_26 (GPIO_4 ) - Pino de leitura da bateria

#define MOTOR_FL_PIN1        32             // PIN_7  (GPIO_32) - Pino de controle do motor FL (motor1)
#define MOTOR_FL_PIN2        33             // PIN_8  (GPIO_33) - Pino de controle do motor FL (motor1)
#define MOTOR_FR_PIN1        34             // PIN_5  (GPIO_34) - Pino de controle do motor FR (motor2)
#define MOTOR_FR_PIN2        35             // PIN_6  (GPIO_35) - Pino de controle do motor FR (motor2)
#define MOTOR_RL_PIN1        10             // PIN_17 (GPIO_10) - Pino de controle do motor RL (motor3)
#define MOTOR_RL_PIN2        11             // PIN_18 (GPIO_11) - Pino de controle do motor RL (motor3)
#define MOTOR_RR_PIN1        13             // PIN_15 (GPIO_13) - Pino de controle do motor RR (motor4)
#define MOTOR_RR_PIN2         9             // PIN_16 (GPIO_9 ) - Pino de controle do motor RR (motor4)

//-----------------------------------------------------------------------------------------------------------
//   Comunicação Serial

#define BAUD_RATE 9600                      // Taxa de transmissão da Serial Monitor [bps] 

//-----------------------------------------------------------------------------------------------------------
//   Obstáculos

#define MIN_DISTANCE 20                     // Distância mínima para detectar um obstáculo [cm]

//-----------------------------------------------------------------------------------------------------------
//   Buzzer (PWM)

#define BUZZER_CHANNEL       0              // Canal PWM do buzzer (speaker)
#define BUZZER_FREQUENCY     1000           // Frequência do PWM do buzzer (speaker) [Hz]
#define BUZZER_RESOLUTION    8              // Resolução do PWM do buzzer (speaker) [bits]
#define BUZZER_DUTY_CYCLE    128            // Duty cycle do PWM do buzzer (speaker) [0-255]

// Um BUZZER_DUTY_CYCLE de 128 significa 50% de duty cycle, pois 128 é metade de 255 (valor máximo em 8 bits).

//-----------------------------------------------------------------------------------------------------------
//   Comunicação Wi-Fi

#define WIFI_NAME "ESP32_Car_Controller"    // Nome da rede Wi-Fi (SSID)
#define WIFI_PASSWORD "123456789"           // Senha da rede Wi-Fi

//-----------------------------------------------------------------------------------------------------------

#endif /* APLIC_HPP */