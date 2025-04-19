#ifndef TASK_EYES_HPP
#define TASK_EYES_HPP

#include "Aplic.hpp"
#include "Modules/EyeAnimator.hpp"

//--------------------------------------------------------------------------------
//   TaskEyes Parameters

#define EYES_PRIORITY 1             // Prioridade da task
#define EYES_DELAY  100             // vTaskDelay em ms
#define EYES_STACK 4096             // Tamanho da stack (bytes)

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

#endif /* TASK_EYES_HPP */
