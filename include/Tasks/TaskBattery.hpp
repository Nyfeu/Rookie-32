#ifndef TASK_BATTERY_HPP
#define TASK_BATTERY_HPP

#include "Aplic.hpp"

/**
 * @class TaskBattery
 * @brief Classe responsável pela verificação do nível de tensão da bateria.
 * 
 * Esta classe encapsula as funcionalidades da medoção do nível de tensão da bateria,
 * via ADC (Analog to Digital Converter).
 */

class TaskBattery {

    public:

        /// Handle da task 
        static TaskHandle_t taskHandle;

        /**
         * @brief Inicia a task de verificação do nível de bateria
         * 
         * Esta função cria a task responsável pela verificação da
         * tensão da bateria, via ADC (Analog to Digital Converter).
         * Resultando no nível de bateria.
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
TaskHandle_t TaskBattery::taskHandle = NULL;

// Implementação do método start()
void TaskBattery::start() {

    // Inicializa a task do FreeRTOS
    BaseType_t result = xTaskCreate(taskFunction, "TaskBattery", BATTERY_STACK, NULL, BATTERY_PRIORITY, &taskHandle);

    if (result != pdPASS) Serial.println("TaskBattery: [FAILED]");
    else Serial.println("TaskBattery: [OK]");

}

// Implementação da função da task WiFi
void TaskBattery::taskFunction(void *pvParameters) {

    Serial.println("Battery ADC: [OK]");

    xSemaphoreGive(taskBatterySemaphore);

    while (true) {

        // Execution loop: aqui devem ser realizadas as operações periódicas para
        // verificação de obstáculos:

        // Verifica e responde requisições HTTP
        float voltage = battery.readBatteryVoltage();
        float percentage = battery.getBatteryPercentage();

        #if DEBUG_VOLTAGE
            Serial.printf("VOLTAGE: %.2f [V]\nPERCENTAGE: %.1f [%%]\n", voltage, percentage);
        #endif

        // Move a task para o estado 'Blocked' por um intervalo de tempo (em milissegundos), 
        // permitindo que outras tasks sejam executadas durante esse período.
        vTaskDelay(pdMS_TO_TICKS(BATTERY_DELAY));

    }

}

#endif /* TASK_BATTERY_HPP */