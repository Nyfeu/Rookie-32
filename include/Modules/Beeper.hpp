/**
 * @file Beeper.hpp
 * @brief Definição da classe Beeper para controle de um buzzer.
 */

#ifndef _BEEPER_H
#define _BEEPER_H

#include <Arduino.h>
#include "Emotion.hpp"

/**
 * @class Beeper
 * @brief Gerencia a emissão de sons através de um buzzer.
 *
 * Esta classe permite controlar um buzzer conectado a um pino digital,
 * reproduzindo tons específicos ou sequências de tons que representam
 * diferentes "emoções" ou estados do sistema.
 */

class Beeper {
private:

    int buzzerPin; ///< O pino digital ao qual o buzzer está conectado.

    /**
     * @brief Reproduz um tom de uma determinada frequência por uma duração específica.
     * @param frequency A frequência do tom em Hz.
     * @param duration A duração do tom em milissegundos.
     */
    void playTone(int frequency, int duration);

public:

    /**
     * @brief Construtor da classe Beeper.
     * @param pin O pino digital onde o buzzer está conectado.
     */
    Beeper(int pin) : buzzerPin(pin) {}

    /**
     * @brief Reproduz uma sequência de tons associada a uma emoção específica.
     * @details A sequência de tons para cada emoção é pré-definida internamente.
     * @param emotion A emoção (tipo Emotion) a ser reproduzida.
     */
    void playEmotion(Emotion emotion);    

};

#endif /* _BEEPER_H */
