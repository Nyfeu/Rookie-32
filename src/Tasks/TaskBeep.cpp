#include "Tasks/TaskBeep.hpp"
#include "Modules/Beeper.hpp"

// Referência ao beeper (definido em HW.hpp)
extern Beeper beeper;

// Referência ao semáforo da task (definido em Tasks.hpp)
extern SemaphoreHandle_t taskBeeperSemaphore;

// Inicialização do handle da task e da fila
TaskHandle_t TaskBeep::taskHandle = NULL;
QueueHandle_t TaskBeep::beepQueue = NULL;

// Implementação do método start()
void TaskBeep::start() {

    // Criação da fila para armazenar as emoções
    beepQueue = xQueueCreate(10, sizeof(Emotion));

    if (beepQueue == NULL) {
        Serial.println("TaskBeep: [FAILED to create queue]");
        return;
    }

    // Criação da task do FreeRTOS
    BaseType_t result = xTaskCreate(taskFunction, "TaskBeep", BEEP_STACK, NULL, BEEP_PRIORITY, &taskHandle);

    if (result != pdPASS) {
        Serial.println("TaskBeep: [FAILED]");
    } else {
        Serial.println("TaskBeep: [OK]");
    }
}

// Implementação da função da task Beep
void TaskBeep::taskFunction(void *pvParameters) {

    emitBeep(HAPPINESS);
    Emotion emotion;

    xSemaphoreGive(taskBeeperSemaphore);

    while (true) {

        // Aguarda a chegada de uma emoção na fila
        if (xQueueReceive(beepQueue, &emotion, portMAX_DELAY) == pdTRUE) {
            // Emitir o beep para a emoção recebida
            emitBeep(emotion);
        }

        // Permite que outras tasks sejam executadas enquanto a task Beep está aguardando
        vTaskDelay(pdMS_TO_TICKS(BEEP_DELAY));

    }
}

// Implementação da função de emissão do beep
void TaskBeep::emitBeep(Emotion emotion) {
    
    beeper.playEmotion(emotion);

}

// Função para agendar um beep com uma emoção específica
void TaskBeep::triggerBeep(Emotion emotion) {

    // Coloca a emoção na fila para a task Beep processar
    if (xQueueSend(beepQueue, &emotion, portMAX_DELAY) != pdTRUE) {
        Serial.println("TaskBeep: [FAILED TO ENQUEUE EMOTION]");
    }

}