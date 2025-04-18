#ifndef TASK_WIFI_HPP
#define TASK_WIFI_HPP

#include "Aplic.hpp"
#include "TaskBeep.hpp"

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

        #if WDT_ACTIVE

            // Reseta o TWDT (alimenta)
            esp_task_wdt_reset();

        #endif

        // Move a task para o estado 'Blocked' por um intervalo de tempo (em milissegundos), 
        // permitindo que outras tasks sejam executadas durante esse período.
        vTaskDelay(pdMS_TO_TICKS(WIFI_DELAY));

    }

}

#endif /* TASK_WIFI_HPP */