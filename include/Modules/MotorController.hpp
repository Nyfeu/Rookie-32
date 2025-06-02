#ifndef _MOTOR_CONTROLLER_HPP
#define _MOTOR_CONTROLLER_HPP

#include <Arduino.h>
#include "Aplic.hpp"

class MotorController {
private:
  int in1A, in2A, in1B, in2B;
  const float DEAD_ZONE = 0.2;

  void moverFrente();
  void moverTras();
  void virarEsquerda();
  void virarDireita();

public:
  MotorController(int _in1A, int _in2A, int _in1B, int _in2B);
  void pararTodos();
  void begin();
  void handle(float x, float y);
};

#endif /* _MOTOR_CONTROLLER_HPP */
