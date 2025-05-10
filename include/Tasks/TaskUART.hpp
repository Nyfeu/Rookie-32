/**
 * @file TaskUART.hpp
 * @ingroup Tasks
 * @brief Task responsável pela comunicação UART.
 */


#ifndef TASK_UART_HPP
#define TASK_UART_HPP

#include "Aplic.hpp"
#include "TaskBeep.hpp"
#include "Modules/UARTHandler.hpp"

//------------------------------------------------------------------------------
//   TaskUART Parameters

/// Prioridade da TaskUART
#define UART_PRIORITY 3

/// Delay da TaskUART em [ms]
#define UART_DELAY  100

/// Tamanho da stack da TaskUART em [bytes]
#define UART_STACK 4096

/**
 * @class TaskUART
 * @brief Gerencia a comunicação UART via task dedicada.
 * @details Esta classe encapsula as funcionalidades de comunicação UART,
 * criando e gerenciando a task que executa as operações relacionadas.
 */

class TaskUART {

    public:

        /// Handle da task do UART
        static TaskHandle_t taskHandle;

        /**
         * @brief Inicia a task de comunicação UART.
         * @details Cria e configura a task responsável pela comunicação UART.
         * @return void
         */

        static void start();

        /**
         * @brief Função da task responsável pela execução da comunicação UART.
         * @details Função executada periodicamente pela task UART para manter 
         * a comunicação ativa.
         * @param pvParameters Parâmetros fornecidos pela função xTaskCreate,
         *        normalmente utilizados para passar dados para a task.
         * @return void
         */

        static void taskFunction(void *pvParameters);
        
};

#endif /* TASK_UART_HPP */