#ifndef TASK_EYES_HPP
#define TASK_EYES_HPP

#include "Aplic.hpp"
#include "Modules/EyeAnimator.hpp"

//--------------------------------------------------------------------------------
//   TaskEyes Parameters

/// Prioridade da TaskEyes
#define EYES_PRIORITY 1             

/// Delay da TaskEyes em [ms]
#define EYES_DELAY  100             

/// Tamanho da stack da TaskEyes em [bytes]
#define EYES_STACK 4096             

/**
 * @class TaskBeep
 * @brief Classe responsável pelo controle do beep do sistema com diferentes emoções.
 * @details Esta classe encapsula as funcionalidades de controle de beep,
 * criando e gerenciando a task que executa as operações relacionadas.
 */

class TaskEyes {

    public:

        /// Handle da task do Beep
        static TaskHandle_t taskHandle;

        /// Gerenciamento de estado
        static SemaphoreHandle_t mutex;
        static Emotion currentEmotion;

        /// Instância de módulo gerenciador do display
        static EyeAnimator eyes;

        /**
         * @brief Inicia a task de controle dos olhos.
         * @details Cria e configura a task responsável pelo controle dos
         * olhos exibidos no display OLED.
         * @return void
         */
        static void start();

        /**
         * @brief Função da task responsável pela renderização dos olhos.
         * @details Esta é a função executada pela task de de gerenciamento do display. Ela 
         * aguarda até que uma emoção definida, para acionar a exibição correspondente.
         * @param pvParameters Parâmetros fornecidos pela função xTaskCreate,
         *        normalmente utilizados para passar dados para a task.
         * @return void
         */
        static void taskFunction(void *pvParameters);

        /**
         * @brief Altera a emoção exibida nos olhos.
         * @details Esta função permite alterar a emoção atual exibida no display OLED
         * de forma segura, utilizando um mutex para evitar condições de corrida. A nova
         * emoção será aplicada por meio do módulo EyeAnimator.
         * @param newEmotion Emoção a ser exibida (tipo Emotion).
         * @return void
         */
        static void triggerEmotion(Emotion newEmotion) {
            if(xSemaphoreTake(mutex, pdMS_TO_TICKS(100))) {
                eyes.setEmotion(newEmotion);
                xSemaphoreGive(mutex);
            }
        }

};

#endif /* TASK_EYES_HPP */
