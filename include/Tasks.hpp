#ifndef TASKS_HPP
#define TASKS_HPP

//------------------------------------------------------------------------------
//   Inclusões

#include "Aplic.hpp"

//------------------------------------------------------------------------------
//   SemaphoreHandle

SemaphoreHandle_t taskWIFISemaphore;
SemaphoreHandle_t taskObstacleSemaphore;
SemaphoreHandle_t taskBatterySemaphore;
SemaphoreHandle_t taskBeeperSemaphore;
SemaphoreHandle_t taskEyesSemaphore;

//------------------------------------------------------------------------------
//   TaskBeep

#include "Tasks/TaskBeep.hpp"       // Implementação da task

//------------------------------------------------------------------------------
//   TaskEyes

#include "Tasks/TaskEyes.hpp"       // Implementação da task

//------------------------------------------------------------------------------
//   TaskWIFI

#include "Tasks/TaskWiFi.hpp"       // Implementação da task

//------------------------------------------------------------------------------
//   TaskObstacle

#include "Tasks/TaskObstacle.hpp"

//------------------------------------------------------------------------------
//   TaskBattery

#include "Tasks/TaskBattery.hpp"

//------------------------------------------------------------------------------
//   Função: createFreeRTOSTasks

/**
 * @brief Cria e inicializa as tarefas do FreeRTOS.
 *
 * Esta função é responsável por criar as tarefas do sistema utilizando o FreeRTOS.
 * Cada tarefa é configurada com um nome, tamanho da pilha, prioridade e um handle 
 * para gerenciamento. As tarefas criadas incluem:
 * 
 * - `TaskWIFI`: Realiza comunicação via Wi-Fi. 
 */

 void createFreeRTOSTasks() {

    Serial.println("Creating FreeRTOS Tasks...");

    // Criando semáforos para cada task
    taskBeeperSemaphore = xSemaphoreCreateBinary();
    taskWIFISemaphore = xSemaphoreCreateBinary();
    taskObstacleSemaphore = xSemaphoreCreateBinary();
    taskBatterySemaphore = xSemaphoreCreateBinary();
    taskEyesSemaphore = xSemaphoreCreateBinary();

    // Inicializando o TWDT para as tasks com WDT_TIMEOUT
    #if WDT_ACTIVE
        esp_task_wdt_init(WDT_TIMEOUT, true);
    #endif

    // Inicializando as tarefas do sistema:

    TaskBeep::start();
    xSemaphoreTake(taskBeeperSemaphore, portMAX_DELAY);

    TaskWIFI::start();
    xSemaphoreTake(taskWIFISemaphore, portMAX_DELAY);

    TaskObstacle::start();
    xSemaphoreTake(taskObstacleSemaphore, portMAX_DELAY);

    TaskBattery::start();
    xSemaphoreTake(taskBatterySemaphore, portMAX_DELAY);

    TaskEyes::start();
    xSemaphoreTake(taskEyesSemaphore, portMAX_DELAY);

    // Adicionando os TWDTs (Task Watchdog Timer)
    #if WDT_ACTIVE
        esp_task_wdt_add(TaskWIFI::taskHandle);
    #endif

    // Verifica se os TWDTs das tasks foram inicializados adequadamente:
    #if WDT_CHECK

        // TWDT: TaskWIFI
        if (esp_task_wdt_status(TaskWIFI::taskHandle) != ESP_OK) Serial.println("TWDT TaskWIFI: [FAILED]");
        else Serial.println("TWDT TaskWIFI: [OK]");

    #endif

    // Informa que o FreeRTOS foi inicializado apropriadamente:
    Serial.println("FreeRTOS Tasks: [OK]");

};

#endif /* TASKS_HPP */