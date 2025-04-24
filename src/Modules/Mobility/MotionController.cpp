#include "Modules/Mobility/MotionController.hpp"

MotionController::MotionController(IMobilityStrategy* movementStrategy)
    : strategy(movementStrategy) {}

void MotionController::drive(float x, float y) {
    if (strategy) {
        strategy->move(x, y);
    }
}
