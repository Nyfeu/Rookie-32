#include "Modules/ObstacleDetector.hpp"

// Construtor da classe ObstacleDetector
ObstacleDetector::ObstacleDetector(int trig, int echo, int distancia) {
    trigPin = trig;
    echoPin = echo;
    distancia_obstaculo = distancia;            // Define a distância limite para considerar obstáculo [cm]
    callback = nullptr;                         // Inicializa a função de callback como nula
}

// Mede a distância usando o sensor ultrassônico
int ObstacleDetector::measureDistance() {

    // Gera um pulso curto no pino de trigger para iniciar a medição
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Recebe o tempo de resposta no pino de echo e converte para distância em cm
    // Divisão por 58 é uma aproximação comum para converter tempo em microsegundos para centímetros
    return pulseIn(echoPin, HIGH) / 58;

}

bool ObstacleDetector::verify() {

    // Realiza a medição da distância em [cm]
    int distancia = measureDistance();

    #if DEBUG

        // Caso em modo de depuração (DEBUG), imprime a distância lida no monitor serial
        Serial.printf("Distance: %d [cm]\n", distancia);
        
    #endif

    // Se a distância for válida (não zero) e menor ou igual ao limite definido
    if (!(distancia == 0)) {

        // E se a função de callback estiver configurada, ela será chamada
        if (distancia <= distancia_obstaculo && callback) {
            callback();
            return true;
        }

    }

    // Retorna falso se não houver obstáculo ou callback não estiver configurado
    return false;

}