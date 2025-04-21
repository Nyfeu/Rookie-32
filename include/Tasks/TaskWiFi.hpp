#ifndef TASK_WIFI_HPP
#define TASK_WIFI_HPP

#include "Aplic.hpp"
#include "TaskBeep.hpp"
#include "Modules/WiFi_AP.hpp"

//------------------------------------------------------------------------------
//   TaskWIFI Parameters

/// Prioridade das TaskWIFI
#define WIFI_PRIORITY 3

/// Delay da TaskWIFI em [ms]
#define WIFI_DELAY  100

/// Tamanho da stack da TaskWIFI em [bytes]
#define WIFI_STACK 4096

/**
 * @class TaskWIFI
 * @brief Gerencia a comunicação Wi-Fi via task dedicada.
 * @details Esta classe encapsula as funcionalidades de comunicação Wi-Fi,
 * criando e gerenciando a task que executa as operações relacionadas.
 */

class TaskWIFI {

    public:

        /// Handle da task do Wi-Fi
        static TaskHandle_t taskHandle;

        /**
         * @brief Inicia a task de comunicação Wi-Fi.
         * @details Cria e configura a task responsável pela comunicação Wi-Fi.
         * @return void
         */

        static void start();

        /**
         * @brief Função da task responsável pela execução da comunicação Wi-Fi.
         * @details Função executada periodicamente pela task Wi-Fi para manter 
         * a comunicação ativa.
         * @param pvParameters Parâmetros fornecidos pela função xTaskCreate,
         *        normalmente utilizados para passar dados para a task.
         * @return void
         */

        static void taskFunction(void *pvParameters);
        
};

#endif /* TASK_WIFI_HPP */