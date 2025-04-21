#ifndef _BEEPER_H
#define _BEEPER_H

#include <Arduino.h>
#include "Emotion.hpp"

class Beeper {
private:

    int buzzerPin;
    void playTone(int frequency, int duration);

public:

    Beeper(int pin) : buzzerPin(pin) {}
    void playEmotion(Emotion emotion);    

};

#endif /* _BEEPER_H */
