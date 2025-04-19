#ifndef TASK_OBSTACLE_HPP
#define TASK_OBSTACLE_HPP

#include "Aplic.hpp"
#include "TaskBeep.hpp"

//--------------------------------------------------------------------------------
//   TaskObstacle Parameters

#define OBSTACLE_PRIORITY 2         // Prioridade da task
#define OBSTACLE_DELAY  250         // vTaskDelay em ms
#define OBSTACLE_STACK 2048         // Tamanho da stack (bytes)

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

#endif /* TASK_OBSTACLE_HPP */