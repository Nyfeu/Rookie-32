/**
 * @file EyeFrame.hpp
 * @brief Define a estrutura de dados e os frames usados para animações de olhos e expressões faciais.
 * @details Este arquivo fornece uma estrutura para representar um quadro (frame) de uma animação facial,
 * bem como conjuntos de frames pré-definidos para representar emoções específicas como felicidade,
 * calma, tristeza e uma expressão "nerd".
 */

#ifndef EYE_FRAME_HPP
#define EYE_FRAME_HPP

#include "Aplic.hpp"

/**
 * @struct EyeFrame
 * @brief Representa um frame de uma animação facial com olhos esquerdo e direito.
 * @details Essa estrutura permite controlar animações de olhos em displays gráficos,
 * especificando o bitmap de cada olho, dimensões, tempo de exibição e se é uma imagem única.
 * @note Caso singleImage seja verdadeiro, o bitmap é referenciado por leftEye.
 */
struct EyeFrame {
    const uint8_t *leftEye;    ///< Ponteiro para o bitmap do olho esquerdo
    const uint8_t *rightEye;   ///< Ponteiro para o bitmap do olho direito (pode ser nullptr se for uma imagem única)
    uint8_t width;             ///< Largura do bitmap [pixels]
    uint8_t height;            ///< Altura do bitmap  [pixels]
    uint16_t duration;         ///< Duração do frame [ms]
    bool singleImage;          ///< Indica se é uma imagem única (true) ou dois olhos separados (false)
};

// Frames de animação para cada emoção

/**
 * @brief Frames de animação para a emoção HAPPY.
 * @details Composto por dois frames: olhos abertos e semiabertos, criando um piscar animado.
 */
const EyeFrame happyFrames[2] = {
    { 
        happy_open,   // Olho esquerdo aberto
        happy_open,   // Olho direito aberto
        32,           // Largura
        32,           // Altura
        1000,         // Duração 1000ms
        false
    },
    {
        happy_half,   // Olho esquerdo semi-fechado
        happy_half,   // Olho direito semi-fechado
        32,
        32,
        500,
        false
    }
};

/**
 * @brief Frame estático para a expressão NERD.
 * @details Usa uma imagem única que ocupa toda a área dos olhos.
 */
const EyeFrame nerdFrame[1] = {
    {
        nerd_face,
        nullptr,
        128,
        64,
        1000,
        true
    }
};

/**
 * @brief Frame estático para a expressão CALM.
 * @details Usa dois olhos separados, cada um com 16x16 pixels.
 */
const EyeFrame calmFrame[1] = {
    {
        calm_half_left,
        calm_half_right,
        32,
        16,
        100,
        false
    }
};

/**
 * @brief Frame estático para a expressão SADNESS.
 * @details Usa dois olhos separados, cada um com 16x16 pixels.
 */
const EyeFrame sadnessFrame[1] = {
    {
        round_eye_left,
        round_eye_right,
        32,
        16,
        100,
        false
    }
};

#endif /* EYE_FRAME_HPP */