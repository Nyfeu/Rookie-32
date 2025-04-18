#ifndef TASK_EYES_HPP
#define TASK_EYES_HPP

#include "Aplic.hpp"
#include "Modules/EyeAnimator.hpp"

/**
 * @class TaskBeep
 * @brief Classe responsável pelo controle do beep do sistema com diferentes emoções.
 * 
 * Esta classe encapsula as funcionalidades de controle de beep,
 * criando e gerenciando a task que executa as operações relacionadas.
 */
class TaskEyes {

    public:

        /// Handle da task do Beep
        static TaskHandle_t taskHandle;

        /// Gerenciador de estado
        static SemaphoreHandle_t mutex;
        static Emotion currentEmotion;

        /// Instância de gerenciador do display
        static EyeAnimator eyes;

        /**
         * @brief Inicia a task de controle dos olhos.
         * 
         * Esta função cria a task responsável pelo controle dos
         * olhos exibidos no display OLED.
         */
        static void start();

        /**
         * @brief Função da task responsável pela renderização dos olhos.
         * 
         * Esta é a função executada pela task de de gerenciamento do display. Ela 
         * aguarda até que uma emoção definida, para acionar a exibição correspondente.
         * 
         * @param pvParameters Parâmetros fornecidos pela função xTaskCreate,
         *        normalmente utilizados para passar dados para a task.
         */
        static void taskFunction(void *pvParameters);

        static void triggerEmotion(Emotion newEmotion) {
            if(xSemaphoreTake(mutex, pdMS_TO_TICKS(100))) {
                eyes.setEmotion(newEmotion);
                xSemaphoreGive(mutex);
            }
        }

};

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

    // Define a emoção inicial:
    eyes.setEmotion(Emotion::HAPPINESS);
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

#endif /* TASK_EYES_HPP */
