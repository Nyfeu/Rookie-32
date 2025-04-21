#ifndef TASK_OBSTACLE_HPP
#define TASK_OBSTACLE_HPP

#include "Aplic.hpp"
#include "TaskBeep.hpp"

//--------------------------------------------------------------------------------
//   TaskObstacle Parameters

/// Prioridade da TaskObstacle
#define OBSTACLE_PRIORITY 2         

/// Delay da TaskObstacle em [ms]
#define OBSTACLE_DELAY  250         

/// Tamanho da stack da TaskObstacle em [bytes]
#define OBSTACLE_STACK 2048         

/**
 * @class TaskObstacle
 * @brief Classe responsável pela verificação de obstáculos.
 * @details Esta classe encapsula as funcionalidades de detecção de obstáculos,
 * realizadas através do sensor ultrassônico.
 */

class TaskObstacle {

    public:

        /// Handle da TaskObstacle 
        static TaskHandle_t taskHandle;

        /**
         * @brief Inicia a task de verificação de obstáculos
         * @details Cria e configura a task responsável pela verificação de obstáculos.
         * @return void
         */

        static void start();

        /**
         * @brief Função executada pela task em questão.
         * @details Executada periodicamente para verificar obstáculos.
         * @param pvParameters Parâmetros fornecidos pela função xTaskCreate,
         *        normalmente utilizados para passar dados para a task.
         * @return void
         */

        static void taskFunction(void *pvParameters);
        
};

#endif /* TASK_OBSTACLE_HPP */