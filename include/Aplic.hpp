#ifndef APLIC_HPP
#define APLIC_HPP

//--------------------------------------------------------------------
//   Inclusões

#include "Arduino.h"            // Framework do Arduino
#include <freertos/FreeRTOS.h>  // Núcleo do FreeRTOS: permite gerenciamento de tarefas no ESP32
#include <freertos/task.h>      // Manipulação de tarefas (tasks) no FreeRTOS
#include <freertos/semphr.h>    // Gerenciamento de semáforos no FreeRTOS
#include <esp_task_wdt.h>       // Biblioteca do ESP32 para configurar e interagir com o Watchdog Timer

//--------------------------------------------------------------------
//   Gerais

#define ON                   1
#define OFF                  0

//--------------------------------------------------------------------
//   Bateria

#define MAX_BATTERY_VOLTAGE  2.857 // 2.857V = 100% de carga (8.0V na bateria)
#define MIN_BATTERY_VOLTAGE  2.143 // 2.143V = 0.0% de carga (6.0V na bateria)

// Está sendo considerado um divisor de tensão, para limitar a tensão de entrada do ADC a 3.0V
// Um limiar (threshold) é definido a partir de 8.0V na bateria - para 100% da carga

//--------------------------------------------------------------------
//   Debug

#define WDT_CHECK       ON      // Verifica inicialização dos TWDTs
#define DEBUG_OBSTACLE  OFF     // Verifica sensor de distância
#define DEBUG_VOLTAGE   ON      // Verifica nível de bateria

//--------------------------------------------------------------------
//   Pinout

#define TRIGGER_PIN          33 
#define ECHO_PIN             32 
#define BUZZER_PIN           15 
#define BUZZER_CHANNEL       0  
#define BATT_PIN             34 

//--------------------------------------------------------------------
//   Comunicação Serial

#define BAUD_RATE 9600

//--------------------------------------------------------------------
//   Obstáculos

#define MIN_DISTANCE 20

//--------------------------------------------------------------------
//   Comunicação Wi-Fi

#include "Modules/WiFi_AP.hpp"
#define WIFI_NAME "ESP32_Car_Controller"    // Nome da rede Wi-Fi (SSID)
#define WIFI_PASSWORD "123456789"           // Senha da rede Wi-Fi

//--------------------------------------------------------------------
//   Módulos do sistema

#include "Modules/ObstacleDetector.hpp" // Responsável pelo sensor ultrassônico
#include "Modules/Beeper.hpp"           // Responsável pelo buzzer
#include "Modules/EyeAnimator.hpp"      // Responsável pelo display OLED
#include "Modules/BatteryMonitor.hpp"   // Responsávele pelo ADC da bateria
#include "HW.hpp"                       // Responsável pela inicialização do HW
#include "Tasks.hpp"                    // Responsável pelo gerenciamento de tasks

//--------------------------------------------------------------------
//   


#endif /* APLIC_HPP */