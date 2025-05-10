#include "Tasks/TaskEyes.hpp"

// Referência ao semáforo da task (definido em Tasks.hpp)
extern SemaphoreHandle_t taskEyesSemaphore;

// Referência ao mutex de inicialização (definido em Tasks.hpp)
extern SemaphoreHandle_t initMutex;

// Inicialização do handle da task e da fila
TaskHandle_t TaskEyes::taskHandle = NULL;

// Implementação do método start()
void TaskEyes::start() {

    // Inicializa hardware
    if(!eyes.begin()) Serial.println("OLED DISPLAY: [NOT FOUND]");
    Serial.println("OLED DISPLAY: [OK]");

    // Cria mutex para acesso seguro
    mutex = xSemaphoreCreateMutex();

    // Criação da task do FreeRTOS
    BaseType_t result = xTaskCreate(taskFunction, "TaskEyes", EYES_STACK, NULL, EYES_PRIORITY, &taskHandle);

    if (result != pdPASS) {
        Serial.println("TaskEyes: [FAILED]");
    } else {
        Serial.println("TaskEyes: [OK]");
    }
}

// Implementação da função da task Beep
void TaskEyes::taskFunction(void *pvParameters) {

    // Inicializa o semáforo de inicialização da task
    xSemaphoreTake(initMutex, portMAX_DELAY);

    // Define a emoção inicial:
    eyes.setEmotion(Emotion::HAPPINESS);

    // Libera o semáforo de inicialização
    xSemaphoreGive(initMutex);

    // Libera o semáforo da task
    xSemaphoreGive(taskEyesSemaphore);

    while (true) {

        // Realiza a animação
        // Atualização segura do frame
        xSemaphoreTake(mutex, portMAX_DELAY);
        eyes.updateAnimation();
        xSemaphoreGive(mutex);

        // Permite que outras tasks sejam executadas enquanto a task Beep está aguardando
        vTaskDelay(pdMS_TO_TICKS(EYES_DELAY));

    }

}

// Inicializa componentes estáticos
SemaphoreHandle_t TaskEyes::mutex = NULL;
Emotion TaskEyes::currentEmotion = HAPPINESS;
EyeAnimator TaskEyes::eyes;