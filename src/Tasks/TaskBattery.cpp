#include "Tasks/TaskBattery.hpp"
#include "Modules/BatteryMonitor.hpp"

// Referência ao leitor de bateria (definido em HW.hpp)
extern BatteryMonitor battery;

// Referência ao semáforo da task (definido em Tasks.hpp)
extern SemaphoreHandle_t taskBatterySemaphore;

// Referência ao mutex de inicialização (definido em Tasks.hpp)
extern SemaphoreHandle_t initMutex;

// Inicialização do handle da task, como NULL
TaskHandle_t TaskBattery::taskHandle = NULL;

// Implementação do método start()
void TaskBattery::start() {

    // Inicializa a task do FreeRTOS
    BaseType_t result = xTaskCreate(taskFunction, "TaskBattery", BATTERY_STACK, NULL, BATTERY_PRIORITY, &taskHandle);

    if (result != pdPASS) Serial.println("TaskBattery: [FAILED]");
    else Serial.println("TaskBattery: [OK]");

}

// Implementação da função da task battery
void TaskBattery::taskFunction(void *pvParameters) {

    // Inicializa o semáforo de inicialização da task
    xSemaphoreTake(initMutex, portMAX_DELAY);

    // Inicialização do ADC para leitura da bateria
    Serial.println("Battery ADC: [OK]");

    // Libera o semáforo de inicialização
    xSemaphoreGive(initMutex);

    // Libera o semáforo da task
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