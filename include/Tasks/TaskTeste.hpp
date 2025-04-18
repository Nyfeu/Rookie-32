#ifndef TASK_TESTE_HPP
#define TASK_TESTE_HPP

#include "Aplic.hpp"

/**
 * @class TaskWIFI
 * @brief Classe responsável pela comunicação Wi-Fi do sistema.
 * 
 * Esta classe encapsula as funcionalidades de comunicação Wi-Fi,
 * criando e gerenciando a task que executa as operações relacionadas.
 */

class TaskTeste {
    
    private:
        
        static TaskHandle_t taskHandle;

    public:

        static BaseType_t start();

        static void taskFunction(void *pvParameters);
        
};

// Inicialização do handle da task, como NULL
TaskHandle_t TaskTeste::taskHandle = NULL;

// Implementação do método start()
BaseType_t TaskTeste::start() {
    return xTaskCreate(taskFunction, "Teste Task", 256, NULL, WIFI_PRIORITY, &taskHandle);
}

// Implementação da função da task WiFi
void TaskTeste::taskFunction(void *pvParameters) {

    while (true) {
        Serial.println("Task de teste executando...");
        vTaskDelay(pdMS_TO_TICKS(500));  // Delay de 500ms
    }

}

#endif /* TASK_TESTE_HPP */