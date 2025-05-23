#include "Aplic.hpp"
#include "Tasks/TaskBluetooth.hpp"
#include "Tasks/TaskEyes.hpp"

// Referência ao semáforo da task (definido em Tasks.hpp)
extern SemaphoreHandle_t taskBluetoothSemaphore;

// Referência ao mutex de inicialização (definido em Tasks.hpp)
extern SemaphoreHandle_t initMutex;

// Inicialização do handle da task, como NULL
TaskHandle_t TaskBluetooth::taskHandle = NULL;

// Implementação do método start()
void TaskBluetooth::start() {

    // Inicializa a task do FreeRTOS
    BaseType_t result = xTaskCreate(taskFunction, "TaskBluetooth", BLUETOOTH_STACK, NULL, BLUETOOTH_PRIORITY, &taskHandle);

    if (result != pdPASS) Serial.println("TaskBluetooth: [FAILED]");
    else Serial.println("TaskBluetooth: [OK]");

}

// Implementação da função da task Bluetooth
void TaskBluetooth::taskFunction(void *pvParameters) {

    // Inicializa o semáforo de inicialização da task
    xSemaphoreTake(initMutex, portMAX_DELAY);
    
    // Inicialização da comunicação serial
    BluetoothHandler bluetoothHandler;

    bluetoothHandler.setSoundCallback([](Emotion emotion) {
        TaskEyes::triggerEmotion(emotion);
        TaskBeep::triggerBeep(emotion);
    });

    bluetoothHandler.begin();

    Serial.println("Bluetooth Handler: [OK]");

    // Libera o semáforo de inicialização
    xSemaphoreGive(initMutex);

    // Libera o semáforo da task
    xSemaphoreGive(taskBluetoothSemaphore);

    while (true) {

        // Execution loop: aqui devem ser realizadas as operações periódicas de comunicação
        // Bluetooth, como receber pacotes.

        // Verifica os comandos recebidos via Bluetooth
        bluetoothHandler.handleClient();

        // Reseta o TWDT (alimenta)
        esp_task_wdt_reset();

        // Move a task para o estado 'Blocked' por um intervalo de tempo (em milissegundos), 
        // permitindo que outras tasks sejam executadas durante esse período.
        vTaskDelay(pdMS_TO_TICKS(BLUETOOTH_DELAY));

    }

}