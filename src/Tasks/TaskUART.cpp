#include "Aplic.hpp"
#include "Tasks/TaskUART.hpp"
#include "Tasks/TaskEyes.hpp"

// Referência ao semáforo da task (definido em Tasks.hpp)
extern SemaphoreHandle_t taskUARTSemaphore;

// Referência ao mutex de inicialização (definido em Tasks.hpp)
extern SemaphoreHandle_t initMutex;

// Inicialização do handle da task, como NULL
TaskHandle_t TaskUART::taskHandle = NULL;

// Implementação do método start()
void TaskUART::start() {

    // Inicializa a task do FreeRTOS
    BaseType_t result = xTaskCreate(taskFunction, "TaskUART", UART_STACK, NULL, UART_PRIORITY, &taskHandle);

    if (result != pdPASS) Serial.println("TaskUART: [FAILED]");
    else Serial.println("TaskUART: [OK]");

}

// Implementação da função da task UART
void TaskUART::taskFunction(void *pvParameters) {

    // Inicializa o semáforo de inicialização da task
    xSemaphoreTake(initMutex, portMAX_DELAY);
    
    // Inicialização da comunicação serial
    UartHandler UARThandler(Serial1, UART_RX_PIN, UART_TX_PIN, UART_BAUD_RATE);

    UARThandler.setSoundCallback([](Emotion emotion) {
        TaskEyes::triggerEmotion(emotion);
        TaskBeep::triggerBeep(emotion);
    });

    UARThandler.begin();

    Serial.println("UART Handler: [OK]");

    // Libera o semáforo de inicialização
    xSemaphoreGive(initMutex);

    // Libera o semáforo da task
    xSemaphoreGive(taskUARTSemaphore);

    while (true) {

        // Execution loop: aqui devem ser realizadas as operações periódicas de comunicação
        // UART, como receber pacotes.

        // Verifica os comandos recebidos via UART
        UARThandler.handleClient();

        // Reseta o TWDT (alimenta)
        esp_task_wdt_reset();

        // Move a task para o estado 'Blocked' por um intervalo de tempo (em milissegundos), 
        // permitindo que outras tasks sejam executadas durante esse período.
        vTaskDelay(pdMS_TO_TICKS(UART_DELAY));

    }

}