/**
 * @file ObstacleDetector.hpp
 * @brief Definição da classe ObstacleDetector para detecção de obstáculos usando sensor ultrassônico.
 */

#ifndef _OBSTACLE_DETECTOR_H
#define _OBSTACLE_DETECTOR_H

#include "Arduino.h"
#include "Aplic.hpp"

/**
 * @class ObstacleDetector
 * @brief Gerencia a detecção de obstáculos usando um sensor ultrassônico HC-SR04.
 *
 * Esta classe fornece métodos para medir distâncias e verificar a presença de obstáculos,
 * disparando um callback opcional quando um obstáculo é detectado dentro de uma distância limite.
 */
class ObstacleDetector {
    
private:

    int trigPin;              ///< Pino TRIGGER do sensor ultrassônico.
    int echoPin;              ///< Pino ECHO do sensor ultrassônico.
    int distancia_obstaculo;  ///< Distância limite em cm para considerar um obstáculo.
    void (*callback)();       ///< Ponteiro para a função de callback a ser chamada quando um obstáculo é detectado.

public:

    /**
     * @brief Construtor da classe ObstacleDetector.
     * @param trig O pino TRIGGER do sensor ultrassônico.
     * @param echo O pino ECHO do sensor ultrassônico.
     * @param distancia A distância máxima em centímetros para considerar a detecção de um obstáculo.
     */
    ObstacleDetector(int trig, int echo, int distancia);

    /**
     * @brief Define a função de callback a ser executada quando um obstáculo é detectado.
     * @param func Ponteiro para a função de callback (sem parâmetros e sem retorno).
     */
    void setCallback(void (*func)()) {
        callback = func;
    }

    /**
     * @brief Mede a distância usando o sensor ultrassônico.
     * @details A função envia um pulso ultrassônico e mede o tempo de retorno para calcular a distância.
     * @return A distância medida em centímetros.
     */
    int measureDistance();

    /**
     * @brief Verifica a presença de obstáculos.
     * @details Se a distância medida for menor ou igual a `distancia_obstaculo` e uma função de callback
     * estiver configurada, o callback é chamado.
     * @return `true` se um obstáculo for detectado e o callback for chamado, `false` caso contrário.
     */
    bool verify();

};

#endif /* _OBSTACLE_DETECTOR_H */
  