#include "Arduino.h"
#include "Modules/Mobility/MotorController.hpp"

MotorController::MotorController(int pin1, int pin2, int channel1, int channel2)
    : motorPin1(pin1), motorPin2(pin2), pwmChannel1(channel1), pwmChannel2(channel2), 
      motorSpeed(0), motorDirection(STOP)
{
    ledcSetup(pwmChannel1, pwmFreq, pwmResolution);
    ledcAttachPin(motorPin1, pwmChannel1);

    ledcSetup(pwmChannel2, pwmFreq, pwmResolution);
    ledcAttachPin(motorPin2, pwmChannel2);

    updateOutput();
}

void MotorController::setSpeed(int speed) {
    motorSpeed = constrain(speed, 0, 255);
    updateOutput();
}

void MotorController::setDirection(Direction direction) {
    motorDirection = direction;
    updateOutput();
}

void MotorController::updateOutput() {

    switch (motorDirection) {
        case FORWARD:
            ledcWrite(pwmChannel1, motorSpeed);
            ledcWrite(pwmChannel2, 0);
            break;
        case BACKWARD:
            ledcWrite(pwmChannel1, 0);
            ledcWrite(pwmChannel2, motorSpeed);
            break;
        case STOP:
        default:
            ledcWrite(pwmChannel1, 0);
            ledcWrite(pwmChannel2, 0);
            break;
    }

}