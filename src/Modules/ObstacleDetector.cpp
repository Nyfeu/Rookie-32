#include "Modules/ObstacleDetector.hpp"

ObstacleDetector::ObstacleDetector(int trig, int echo, int distancia) {
    trigPin = trig;
    echoPin = echo;
    distancia_obstaculo = distancia;
    callback = nullptr;
}

int ObstacleDetector::measureDistance() {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    return pulseIn(echoPin, HIGH) / 58;

}

bool ObstacleDetector::verify() {

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