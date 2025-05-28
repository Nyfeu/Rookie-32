#include "Modules/MotorController.hpp"

MotorController::MotorController(int _in1A, int _in2A, int _in1B, int _in2B)
    : in1A(_in1A), in2A(_in2A), in1B(_in1B), in2B(_in2B) {}

void MotorController::begin()
{
    int motorPins[] = {in1A, in2A, in1B, in2B};
    for (int i = 0; i < 4; i++)
    {
        pinMode(motorPins[i], OUTPUT);
        digitalWrite(motorPins[i], LOW);
    }
}

void MotorController::pararTodos()
{
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, LOW);
    digitalWrite(in1B, LOW);
    digitalWrite(in2B, LOW);
}

void MotorController::moverTras()
{
    digitalWrite(in1A, HIGH);
    digitalWrite(in2A, LOW);
    digitalWrite(in1B, HIGH);
    digitalWrite(in2B, LOW);
}

void MotorController::moverFrente()
{
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, HIGH);
    digitalWrite(in1B, LOW);
    digitalWrite(in2B, HIGH);
}

void MotorController::virarEsquerda()
{
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, HIGH);
    digitalWrite(in1B, HIGH);
    digitalWrite(in2B, LOW);
}

void MotorController::virarDireita()
{
    digitalWrite(in1A, HIGH);
    digitalWrite(in2A, LOW);
    digitalWrite(in1B, LOW);
    digitalWrite(in2B, HIGH);
}

void MotorController::handle(float x, float y) {

    #if DEBUG_MOTORS == ON
        Serial.printf("MotorController: x = %.2f, y = %.2f\n", x, y);
    #endif

    float distancia = max(abs(x), abs(y));

    if (distancia <= DEAD_ZONE)
        pararTodos();
    else if (abs(y) > abs(x))
    {

        if (y > 0) {
            #if DEBUG_MOTORS == ON
                Serial.println("Movendo para frente");
            #endif
            moverFrente();
        } else {
            #if DEBUG_MOTORS == ON
                Serial.println("Movendo para trás");
            #endif
            moverTras();
        }
    
    } else {

        if (x > 0) {
            #if DEBUG_MOTORS == ON
                Serial.println("Movendo para a direita");
            #endif
            virarDireita();
        } else {
            #if DEBUG_MOTORS == ON
                Serial.println("Movendo para a esquerda");
            #endif
            virarEsquerda();
        }
    }
}
