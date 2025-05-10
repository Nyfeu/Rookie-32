/**
 * @file Tasks.hpp
 * @brief Inicialização e gerenciamento central das tasks do sistema.
 * 
 * @details Este arquivo é responsável por declarar os semáforos e
 * iniciar todas as tasks do sistema FreeRTOS. Inclui os headers individuais
 * de cada task e define a função `createFreeRTOSTasks`, que realiza a
 * criação, sincronização e, se ativado, registro no watchdog timer.
 * 
 * @ingroup Tasks
 */

#ifndef TASKS_HPP
#define TASKS_HPP

//------------------------------------------------------------------------------
//   Inclusões

#include "Aplic.hpp"

//------------------------------------------------------------------------------
//   SemaphoreHandle

/// @ingroup Tasks
/// Semáforo da TaskUART
SemaphoreHandle_t taskUARTSemaphore;

/// @ingroup Tasks
/// Semáforo da TaskObstacle
SemaphoreHandle_t taskObstacleSemaphore;

/// @ingroup Tasks
/// Semáforo da TaskBattery
SemaphoreHandle_t taskBatterySemaphore;

/// @ingroup Tasks
/// Semáforo da TaskBeep
SemaphoreHandle_t taskBeeperSemaphore;

/// @ingroup Tasks
/// Semáforo da TaskEyes
SemaphoreHandle_t taskEyesSemaphore;

/// @ingroup Tasks
/// Mutex de inicialização
SemaphoreHandle_t initMutex;

//------------------------------------------------------------------------------
//   Tasks

#include "Tasks/TaskBeep.hpp"       
#include "Tasks/TaskEyes.hpp"       
#include "Tasks/TaskUART.hpp"      
#include "Tasks/TaskObstacle.hpp"
#include "Tasks/TaskBattery.hpp"

//------------------------------------------------------------------------------
//   Função: createFreeRTOSTasks

/**
 * @brief Cria e inicializa as tarefas do FreeRTOS.
 * @ingroup Tasks
 * @details Esta função é responsável por:
 * - Criar os semáforos globais utilizados para sincronização entre as tasks.
 * - Inicializar cada uma das tasks do sistema via suas respectivas funções `start()`.
 * - Registrar as tasks no Task Watchdog Timer (`esp_task_wdt_add`), se habilitado.
 * - Verificar o status do watchdog (`esp_task_wdt_status`), se habilitado.
 * 
 * Tarefas criadas:
 * - `TaskBeep`: Gerencia sinais sonoros de feedback.
 * - `TaskUART`: Realiza comunicação via UART.
 * - `TaskObstacle`: Faz leitura de sensor de obstáculos.
 * - `TaskBattery`: Monitora nível da bateria.
 * - `TaskEyes`: Controla o display OLED.
 */

 void createFreeRTOSTasks() {

    Serial.println("Creating FreeRTOS Tasks...");

    // Inicializando o mutex de inicialização
    initMutex = xSemaphoreCreateMutex();

    // Criando semáforos para cada task
    taskBeeperSemaphore = xSemaphoreCreateBinary();
    taskUARTSemaphore = xSemaphoreCreateBinary();
    taskObstacleSemaphore = xSemaphoreCreateBinary();
    taskBatterySemaphore = xSemaphoreCreateBinary();
    taskEyesSemaphore = xSemaphoreCreateBinary();

    // Inicializando o TWDT para as tasks com WDT_TIMEOUT
    #if WDT_ACTIVE
        esp_task_wdt_init(WDT_TIMEOUT, true);
    #endif

    // Inicializando as tarefas do sistema:

    TaskBeep::start();
    TaskUART::start();
    TaskObstacle::start();
    TaskBattery::start();
    TaskEyes::start();
    
    // Barreira de sincronização: espera até que todas as tasks estejam prontas
    xSemaphoreTake(taskBeeperSemaphore, portMAX_DELAY);
    xSemaphoreTake(taskUARTSemaphore, portMAX_DELAY);
    xSemaphoreTake(taskObstacleSemaphore, portMAX_DELAY);
    xSemaphoreTake(taskBatterySemaphore, portMAX_DELAY);
    xSemaphoreTake(taskEyesSemaphore, portMAX_DELAY);

    // Adicionando os TWDTs (Task Watchdog Timer)
    #if WDT_ACTIVE
        esp_task_wdt_add(TaskUART::taskHandle);
    #endif

    // Verifica se os TWDTs das tasks foram inicializados adequadamente:
    #if WDT_CHECK

        // TWDT: TaskUART
        if (esp_task_wdt_status(TaskUART::taskHandle) != ESP_OK) Serial.println("TWDT TaskUART: [FAILED]");
        else Serial.println("TWDT TaskUART: [OK]");

    #endif

    // Informa que o FreeRTOS foi inicializado apropriadamente:
    Serial.println("FreeRTOS Tasks: [OK]");

};

#endif /* TASKS_HPP */