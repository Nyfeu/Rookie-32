#include "Aplic.hpp"
#include "Tasks/TaskWiFi.hpp"
#include "Tasks/TaskEyes.hpp"

// Referência ao semáforo da task (definido em Tasks.hpp)
extern SemaphoreHandle_t taskWIFISemaphore;

// Inicialização do handle da task, como NULL
TaskHandle_t TaskWIFI::taskHandle = NULL;

// Implementação do método start()
void TaskWIFI::start() {

    // Inicializa a task do FreeRTOS
    BaseType_t result = xTaskCreate(taskFunction, "TaskWIFI", WIFI_STACK, NULL, WIFI_PRIORITY, &taskHandle);

    if (result != pdPASS) Serial.println("TaskWIFI: [FAILED]");
    else Serial.println("TaskWIFI: [OK]");

}

// Implementação da função da task WiFi
void TaskWIFI::taskFunction(void *pvParameters) {

    // Inicialização com SSID e senha
    WiFi_AP carController(WIFI_NAME, WIFI_PASSWORD);
    carController.begin();

    carController.setClientConnectCallback([]() { 
        TaskBeep::triggerBeep(CALM); 
    });

    carController.setClientDisconnectCallback([]() {
        TaskBeep::triggerBeep(SADNESS);
    });

    carController.setSoundCallback([](Emotion emotion) {
        TaskEyes::triggerEmotion(emotion);
        TaskBeep::triggerBeep(emotion);
    });

    Serial.println("WIFI AP Controller: [OK]");

    xSemaphoreGive(taskWIFISemaphore);

    while (true) {

        // Execution loop: aqui devem ser realizadas as operações periódicas de comunicação
        // Wi-Fi, como enviar/receber pacotes, verificar status, etc.

        // Verifica e responde requisições HTTP
        carController.handleClient();

        // Reseta o TWDT (alimenta)
        esp_task_wdt_reset();

        // Move a task para o estado 'Blocked' por um intervalo de tempo (em milissegundos), 
        // permitindo que outras tasks sejam executadas durante esse período.
        vTaskDelay(pdMS_TO_TICKS(WIFI_DELAY));

    }

}