/**
 * @file TaskBeep.hpp
 * @ingroup Tasks
 * @brief Task responsável pela emissão de beeps de feedback.
 */

#ifndef TASK_BEEP_HPP
#define TASK_BEEP_HPP

#include "Aplic.hpp"
#include "Emotion.hpp"

//--------------------------------------------------------------------------------
//   TaskBeep Parameters

/// Prioridade da TaskBeep
#define BEEP_PRIORITY 1             

/// Delay da TaskBeep em [ms]
#define BEEP_DELAY  100             

/// Tamanho da stack da TaskBeep em [bytes]
#define BEEP_STACK 4096             

/**
 * @class TaskBeep
 * @brief Classe responsável pelo controle do beep do sistema com diferentes emoções.
 * @details Esta classe encapsula as funcionalidades de controle de beep,
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
         * @details Cria e configura a task responsável pelo controle do beep,
         * configurando o ambiente necessário para a operação da task.
         */
        static void start();

        /**
         * @brief Função da task responsável pela execução do beep.
         * @details Esta é a função executada pela task de controle do beep. Ela 
         * aguarda até que uma emoção seja colocada na fila para emitir o beep 
         * correspondente.
         * @param pvParameters Parâmetros fornecidos pela função xTaskCreate,
         *        normalmente utilizados para passar dados para a task.
         * @return void
         */
        static void taskFunction(void *pvParameters);

        /**
         * @brief Função para agendar um beep com uma emoção específica.
         * @details Esta função coloca uma emoção na fila para que a task de beep
         * a processe posteriormente.
         * @param emotion A emoção (tipo Emotion) - podendo ser: HAPPINESS, ANXIETY, etc.
         * @return void
         */
        static void triggerBeep(Emotion emotion);

    private:

        /**
         * @brief Função para emitir o beep.
         * @details Esta função pode ser chamada para emitir um beep imediatamente.
         * @param emotion A emoção (tipo Emotion) - podendo ser: HAPPINESS, ANXIETY, etc.
         * @return void
         */
        static void emitBeep(Emotion emotion);

};

#endif /* TASK_BEEP_HPP */
