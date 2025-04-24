#include "Modules/Mobility/FourWheelDrive.hpp"
#include <algorithm>
#include <cmath>

FourWheelDrive::FourWheelDrive(
    MotorController* fl, MotorController* fr,
    MotorController* rl, MotorController* rr,
    int maxSpd
) : frontLeft(fl), frontRight(fr), rearLeft(rl), rearRight(rr), maxSpeed(maxSpd) {}

void FourWheelDrive::apply(MotorController* m, float pwr) {
    if (pwr > 0.01f) {
        m->setDirection(FORWARD);
        m->setSpeed(pwr * maxSpeed);
    } else if (pwr < -0.01f) {
        m->setDirection(BACKWARD);
        m->setSpeed(-pwr * maxSpeed);
    } else {
        m->setDirection(STOP);
        m->setSpeed(0);
    }   
}

void FourWheelDrive::move(float x, float y) {

    float leftPower = y + x;
    float rightPower = y - x;

    float maxMag = std::max(std::max(fabs(leftPower), fabs(rightPower)), 1.0f);

    leftPower /= maxMag;
    rightPower /= maxMag;

    apply(frontLeft, leftPower);
    apply(rearLeft, leftPower);
    apply(frontRight, rightPower);
    apply(rearRight, rightPower);

}
