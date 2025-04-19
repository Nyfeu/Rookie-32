#ifndef _BEEPER_H
#define _BEEPER_H

#include <Arduino.h>
#include "Emotion.hpp"

class Beeper {
private:

    int buzzerPin;

public:

    Beeper(int pin) : buzzerPin(pin) {}
    void playTone(int frequency, int duration);
    void playEmotion(Emotion emotion);    

};

#endif /* _BEEPER_H */
