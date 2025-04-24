#ifndef MOTOR_CONTROLLER_HPP
#define MOTOR_CONTROLLER_HPP

#include <Arduino.h>

enum Direction {
    FORWARD = 1,
    STOP = 0,
    BACKWARD = -1
};    

class MotorController {
    
    private: 

        int motorPin1;              
        int motorPin2;              
        int pwmChannel1;           
        int pwmChannel2;           
        int motorSpeed;             
        Direction motorDirection;   

        static const int pwmFreq = 20000;
        static const int pwmResolution = 8;

        void updateOutput();

    public:

        MotorController(int pin1, int pin2, int channel1, int channel2);

        void setSpeed(int speed);
        void setDirection(Direction direction);

};

#endif /* MOTOR_CONTROLLER_HPP */
