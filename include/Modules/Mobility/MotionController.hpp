#ifndef MOTION_CONTROLLER_HPP
#define MOTION_CONTROLLER_HPP

#include "IMobilityStrategy.hpp"

class MotionController {
    private:
        IMobilityStrategy* strategy;

    public:
        MotionController(IMobilityStrategy* movementStrategy);
        void drive(float x, float y);
};

#endif /* MOTION_CONTROLLER_HPP */