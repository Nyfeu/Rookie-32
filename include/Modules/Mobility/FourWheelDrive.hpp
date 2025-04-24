#ifndef FOUR_WHEEL_DRIVE_HPP
#define FOUR_WHEEL_DRIVE_HPP

#include "IMobilityStrategy.hpp"
#include "MotorController.hpp"

class FourWheelDrive : public IMobilityStrategy {
    private:
        MotorController* frontLeft;
        MotorController* frontRight;
        MotorController* rearLeft;
        MotorController* rearRight;
        int maxSpeed;

        void apply(MotorController* m, float power);

    public:
        FourWheelDrive(
            MotorController* fl,
            MotorController* fr,
            MotorController* rl,
            MotorController* rr,
            int maxSpd = 255
        );

        void move(float x, float y) override;
};

#endif
