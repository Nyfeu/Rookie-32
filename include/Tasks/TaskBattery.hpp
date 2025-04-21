#ifndef TASK_BATTERY_HPP
#define TASK_BATTERY_HPP

#include "Aplic.hpp"

//--------------------------------------------------------------------------------
//   TaskBattery Parameters

/// Prioridade da TaskBattery
#define BATTERY_PRIORITY 1          

/// Delay da TaskBattery em [ms]
#define BATTERY_DELAY 5000          

/// Tamanho da stack da TaskBattery em [bytes]
#define BATTERY_STACK 4096          

/**
 * @class TaskBattery
 * @brief Classe responsável pela verificação do nível de tensão da bateria.
 * @details Esta classe encapsula as funcionalidades da medoção do nível de tensão da bateria,
 * via ADC (Analog to Digital Converter).
 */

class TaskBattery {

    public:

        /// Handle da TaskBattery
        static TaskHandle_t taskHandle;

        /**
         * @brief Inicia a task de verificação do nível de bateria
         * @details Esta função cria a task responsável pela verificação da
         * tensão da bateria, via ADC (Analog to Digital Converter).
         * Resultando no nível de bateria.
         * @return void
         */

        static void start();

        /**
         * @brief Esta é a função executada pela task.
         * @param pvParameters Parâmetros fornecidos pela função xTaskCreate,
         *        normalmente utilizados para passar dados para a task.
         * @return void
         */

        static void taskFunction(void *pvParameters);
        
};

#endif /* TASK_BATTERY_HPP */