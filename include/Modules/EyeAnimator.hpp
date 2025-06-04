/**
 * @file EyeAnimator.hpp
 * @brief Definição da classe EyeAnimator para controlar animações de olhos em um display OLED.
 */

#ifndef EYE_ANIMATOR_HPP
#define EYE_ANIMATOR_HPP

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Emotion.hpp"             // Inclui a enumeração Emotion para gerenciar estados emocionais
#include "Assets/BitMaps.hpp"      // Inclui os bitmaps das imagens dos olhos
#include "Assets/EyeFrame.hpp"     // Inclui a estrutura EyeFrame e as definições de frames

/** @defgroup EyeAnimator_Macros Macros de Configuração do EyeAnimator
 * @{
 */

/**
 * @brief Largura da tela do display OLED em pixels.
 */
#define SCREEN_WIDTH    128

/**
 * @brief Altura da tela do display OLED em pixels.
 */
#define SCREEN_HEIGHT    64

/**
 * @brief Altura do bitmap de um olho em pixels.
 */
#define EYE_HEIGHT       32

/**
 * @brief Pino de reset para o display OLED (usar -1 se não houver pino de reset físico).
 */
#define OLED_RESET       -1

/**
 * @brief Endereço I2C do display OLED.
 */
#define SCREEN_ADDRESS 0x3C

/** @} */ // Fim do grupo EyeAnimator_Macros


/**
 * @class EyeAnimator
 * @brief Gerencia a animação e exibição de "olhos" em um display OLED.
 *
 * Esta classe é responsável por inicializar o display OLED, definir e atualizar
 * as emoções exibidas (que são representadas por animações de olhos),
 * e desenhar os frames correspondentes na tela.
 */
class EyeAnimator {

    private:

        Adafruit_SSD1306 display;  ///< Objeto do display OLED.
        Emotion currentEmotion;    ///< A emoção atualmente exibida pelos olhos.
        unsigned long lastUpdate;  ///< O último momento em que a animação foi atualizada.
        uint8_t animationFrame;    ///< O índice do frame atual da animação.

    public:

        /**
         * @brief Construtor da classe EyeAnimator.
         * @details Inicializa o objeto do display com a largura, altura e endereço I2C,
         * define a emoção inicial como HAPPINESS, e reseta os contadores de tempo e frame.
         */
        EyeAnimator() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), 
                    currentEmotion(HAPPINESS), lastUpdate(0), animationFrame(0) {}

        /**
         * @brief Inicializa o display OLED.
         * @return `true` se o display foi inicializado com sucesso, `false` caso contrário.
         */
        bool begin();

        /**
         * @brief Define a nova emoção a ser exibida.
         * @details Se a nova emoção for diferente da atual, a animação é reiniciada
         * para o primeiro frame da nova emoção.
         * @param newEmotion A nova emoção a ser definida.
         */
        void setEmotion(Emotion newEmotion);

        /**
         * @brief Atualiza o frame atual da animação dos olhos.
         * @details Esta função avança para o próximo frame da animação se o tempo
         * de duração do frame atual tiver passado, e redesenha os olhos no display.
         */
        void updateAnimation();

    private:

        /**
         * @brief Retorna o frame atual da animação com base na emoção atual e no índice do frame.
         * @return Uma referência constante para a estrutura EyeFrame do frame atual.
         */
        const EyeFrame& getCurrentFrame();

        /**
         * @brief Retorna o número total de frames para a emoção atual.
         * @return O número de frames para a emoção atual.
         */
        uint8_t getFrameCount();

        /**
         * @brief Desenha os olhos no display OLED.
         * @details Esta função limpa o display e desenha o bitmap do olho esquerdo e direito
         * (ou uma imagem única, dependendo do frame) na posição centralizada.
         */
        void drawEyes();

};

#endif /* EYE_ANIMATOR_HPP */