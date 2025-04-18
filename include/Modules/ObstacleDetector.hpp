#ifndef _OBSTACLE_DETECTOR_H
#define _OBSTACLE_DETECTOR_H

#include "Arduino.h"

class ObstacleDetector {
    
private:

    int trigPin;
    int echoPin;
    int distancia_obstaculo;
    void (*callback)();

public:

    // Construtor da classe
    ObstacleDetector(int trig, int echo, int distancia) {

        trigPin = trig;
        echoPin = echo;
        distancia_obstaculo = distancia;
        callback = nullptr;

    }

    // Setter: callback function
    void setCallback(void (*func)()) {

        callback = func;

    }

    // Função para medir a distância
    int measureDistance() {

        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        return pulseIn(echoPin, HIGH) / 58;

    }

    // Função para verificar a presença de obstáculo e exibir no monitor serial
    bool verify() {

        int distancia = measureDistance();

        #if DEBUG

            Serial.printf("Distance: %d [cm]\n", distancia);
            
        #endif

        if (!(distancia == 0)) {
            if (distancia <= distancia_obstaculo && callback) {
                callback();
                return true;
            }
        }

        return false;

    }

};

#endif /* _OBSTACLE_DETECTOR_H */
  