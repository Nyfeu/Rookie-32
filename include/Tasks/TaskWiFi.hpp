#ifndef TASK_WIFI_HPP
#define TASK_WIFI_HPP

#include "Aplic.hpp"
#include "TaskBeep.hpp"
#include "Modules/WiFi_AP.hpp"

//------------------------------------------------------------------------------
//   TaskWIFI Parameters

#define WIFI_PRIORITY 3             // Prioridade da task
#define WIFI_DELAY  100             // vTaskDelay em ms
#define WIFI_STACK 4096             // Tamanho da stack (bytes)

/**
 * @class TaskWIFI
 * @brief Classe responsável pela comunicação Wi-Fi do sistema.
 * 
 * Esta classe encapsula as funcionalidades de comunicação Wi-Fi,
 * criando e gerenciando a task que executa as operações relacionadas.
 */

class TaskWIFI {

    public:

        /// Handle da task do Wi-Fi
        static TaskHandle_t taskHandle;

        /**
         * @brief Inicia a task de comunicação Wi-Fi.
         * 
         * Esta função cria a task responsável pela comunicação Wi-Fi,
         * configurando o ambiente necessário para a operação da task.
         */

        static void start();

        /**
         * @brief Função da task responsável pela execução da comunicação Wi-Fi.
         * 
         * Esta é a função executada pela task de comunicação Wi-Fi. Ela 
         * é executada periodicamente em loop para garantir a comunicação. 
         * 
         * @param pvParameters Parâmetros fornecidos pela função xTaskCreate,
         *        normalmente utilizados para passar dados para a task.
         */

        static void taskFunction(void *pvParameters);
        
};

#endif /* TASK_WIFI_HPP */