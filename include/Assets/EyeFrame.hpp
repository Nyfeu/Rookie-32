#ifndef EYE_FRAME_HPP
#define EYE_FRAME_HPP

#include "Aplic.hpp"

// Estrutura para armazenar frames de animação
struct EyeFrame {
    const uint8_t *leftEye;
    const uint8_t *rightEye;
    uint8_t width;
    uint8_t height;
    uint16_t duration;
    bool singleImage;
};

/// Frames de animação para cada emoção
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