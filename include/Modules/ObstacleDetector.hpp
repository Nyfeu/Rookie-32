#ifndef _OBSTACLE_DETECTOR_H
#define _OBSTACLE_DETECTOR_H

#include "Arduino.h"
#include "Aplic.hpp"

class ObstacleDetector {
    
private:

    int trigPin;
    int echoPin;
    int distancia_obstaculo;
    void (*callback)();

public:

    // Construtor da classe
    ObstacleDetector(int trig, int echo, int distancia);

    // Setter: callback function
    void setCallback(void (*func)()) {
        callback = func;
    }

    // Função para medir a distância
    int measureDistance();

    // Função para verificar a presença de obstáculo e exibir no monitor serial
    bool verify();

};

#endif /* _OBSTACLE_DETECTOR_H */
  