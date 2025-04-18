#ifndef TASK_OBSTACLE_HPP
#define TASK_OBSTACLE_HPP

#include "Aplic.hpp"
#include "TaskBeep.hpp"

/**
 * @class TaskObstacle
 * @brief Classe responsável pela verificação de obstáculos.
 * 
 * Esta classe encapsula as funcionalidades de detecção de obstáculos,
 * realizadas através do sensor ultrassônico.
 */

class TaskObstacle {

    public:

        /// Handle da task 
        static TaskHandle_t taskHandle;

        /**
         * @brief Inicia a task de verificação de obstáculos
         * 
         * Esta função cria a task responsável pela verificação de 
         * obstáculos, gerenciando os argumentos para o sensoriamento,
         * assim como o as ações a serem tomadas caso seja detectado 
         * um obstáculo.
         */

        static void start();

        /**
         * @brief Esta é a função executada pela task.
         * 
         * @param pvParameters Parâmetros fornecidos pela função xTaskCreate,
         *        normalmente utilizados para passar dados para a task.
         */

        static void taskFunction(void *pvParameters);
        
};

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
        if (detector.verify()) Serial.println("OBSTACLE: [DETECTED]");

        // Move a task para o estado 'Blocked' por um intervalo de tempo (em milissegundos), 
        // permitindo que outras tasks sejam executadas durante esse período.
        vTaskDelay(pdMS_TO_TICKS(OBSTACLE_DELAY));

    }

}

#endif /* TASK_OBSTACLE_HPP */