/**
 * @file TaskBluetooth.hpp
 * @ingroup Tasks
 * @brief Task responsável pela comunicação Bluetooth.
 */


#ifndef TASK_BLUETOOTH_HPP
#define TASK_BLUETOOTH_HPP

#include "Aplic.hpp"
#include "TaskBeep.hpp"
#include "Modules/BluetoothHandler.hpp"

//------------------------------------------------------------------------------
//   TaskBluetooth Parameters

/// Prioridade da TaskBluetooth
#define BLUETOOTH_PRIORITY 3

/// Delay da TaskBluetooth em [ms]
#define BLUETOOTH_DELAY  100

/// Tamanho da stack da TaskBluetooth em [bytes]
#define BLUETOOTH_STACK 4096

/**
 * @class TaskBluetooth
 * @brief Gerencia a comunicação Bluetooth via task dedicada.
 * @details Esta classe encapsula as funcionalidades de comunicação Bluetooth,
 * criando e gerenciando a task que executa as operações relacionadas.
 */

class TaskBluetooth {

    public:

        /// Handle da task do Bluetooth
        static TaskHandle_t taskHandle;

        /**
         * @brief Inicia a task de comunicação Bluetooth.
         * @details Cria e configura a task responsável pela comunicação Bluetooth.
         * @return void
         */

        static void start();

        /**
         * @brief Função da task responsável pela execução da comunicação Bluetooth.
         * @details Função executada periodicamente pela task Bluetooth para manter 
         * a comunicação ativa.
         * @param pvParameters Parâmetros fornecidos pela função xTaskCreate,
         *        normalmente utilizados para passar dados para a task.
         * @return void
         */

        static void taskFunction(void *pvParameters);
        
};

#endif /* TASK_BLUETOOTH_HPP */