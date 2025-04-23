#include "Tasks/TaskObstacle.hpp"
#include "Modules/ObstacleDetector.hpp"

// Referência ao semáforo da task (definido em Tasks.hpp)
extern SemaphoreHandle_t taskObstacleSemaphore;

// Inicialização do handle da task, como NULL
TaskHandle_t TaskObstacle::taskHandle = NULL;

// Implementação do método start()
void TaskObstacle::start() {

    // Inicializa a task do FreeRTOS
    BaseType_t result = xTaskCreate(taskFunction, "TaskObstacle", OBSTACLE_STACK, NULL, OBSTACLE_PRIORITY, &taskHandle);

    if (result != pdPASS) Serial.println("TaskObstacle: [FAILED]");
    else Serial.println("TaskObstacle: [OK]");

}

// Implementação da função da task WiFi
void TaskObstacle::taskFunction(void *pvParameters) {

    // Inicialização do sensor ultrassônico
    ObstacleDetector detector(TRIGGER_PIN, ECHO_PIN, MIN_DISTANCE);
    
    detector.setCallback([]() { 
        TaskBeep::triggerBeep(ANXIETY); 
    });
    
    Serial.println("Obstacle Sensor: [OK]");

    xSemaphoreGive(taskObstacleSemaphore);

    while (true) {

        // Execution loop: aqui são realizadas as operações periódicas para
        // verificação de obstáculos:
        #if DEBUG_OBSTACLE
            if (detector.verify()) Serial.println("OBSTACLE: [DETECTED]");
        #else 
            detector.verify();
        #endif

        // Move a task para o estado 'Blocked' por um intervalo de tempo (em milissegundos), 
        // permitindo que outras tasks sejam executadas durante esse período.
        vTaskDelay(pdMS_TO_TICKS(OBSTACLE_DELAY));

    }

}