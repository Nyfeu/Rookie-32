#ifndef TASK_BEEP_HPP
#define TASK_BEEP_HPP

#include "Aplic.hpp"

/**
 * @class TaskBeep
 * @brief Classe responsável pelo controle do beep do sistema com diferentes emoções.
 * 
 * Esta classe encapsula as funcionalidades de controle de beep,
 * criando e gerenciando a task que executa as operações relacionadas.
 */
class TaskBeep {

    public:

        /// Handle da task do Beep
        static TaskHandle_t taskHandle;

        /// Fila que contém as emoções a serem processadas pela task de beep
        static QueueHandle_t beepQueue;

        /**
         * @brief Inicia a task de controle do beep.
         * 
         * Esta função cria a task responsável pelo controle do beep,
         * configurando o ambiente necessário para a operação da task.
         */
        static void start();

        /**
         * @brief Função da task responsável pela execução do beep.
         * 
         * Esta é a função executada pela task de controle do beep. Ela 
         * aguarda até que uma emoção seja colocada na fila para emitir o beep correspondente.
         * 
         * @param pvParameters Parâmetros fornecidos pela função xTaskCreate,
         *        normalmente utilizados para passar dados para a task.
         */
        static void taskFunction(void *pvParameters);

        /**
         * @brief Função para agendar um beep com uma emoção específica.
         * 
         * Esta função coloca uma emoção na fila para que a task de beep
         * a processe posteriormente.
         * 
         * @param emotion A emoção a ser emitida (HAPPINESS, ANXIETY, etc.).
         */
        static void triggerBeep(Emotion emotion);

    private:

        /**
         * @brief Função para emitir o beep.
         * 
         * Esta função pode ser chamada para emitir um beep imediatamente.
         */
        static void emitBeep(Emotion emotion);

};

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

#endif /* TASK_BEEP_HPP */
