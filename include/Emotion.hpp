/**
 * @file Emotion.hpp
 * @brief Definição da enumeração Emotion para representar estados emocionais do robô.
 */

#ifndef _EMOTION_HPP
#define _EMOTION_HPP

/**
 * @brief Enumeração para selecionar e representar diferentes estados emocionais do robô.
 * @details Essas emoções podem ser usadas para controlar a exibição de olhos no display
 * e a emissão de sons pelo buzzer, proporcionando feedback visual e auditivo.
 */
enum Emotion {
    HAPPINESS,  ///< Representa um estado de felicidade.
    SADNESS,    ///< Representa um estado de tristeza.
    ANXIETY,    ///< Representa um estado de ansiedade ou preocupação.
    CONFUSION,  ///< Representa um estado de confusão.
    CALM,       ///< Representa um estado de calma ou neutralidade.
    ALERT,      ///< Representa um estado de alerta ou atenção.
    ERROR       ///< Representa um estado de erro ou emoção não reconhecida.
};

#endif /* _EMOTION_HPP */