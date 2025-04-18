#ifndef _BEEPER_H
#define _BEEPER_H

#include <Arduino.h>
#include "Emotion.hpp"

// Emoção - Felicidade
const int happiness_tones[][2] = {
    {1500, 80}, {1800, 90}, {2000, 100}, {2300, 110}, 
    {2600, 120}, {2900, 130}, {3100, 140}, {3500, 150}
};

// Emoção - Tristeza
const int sadness_tones[][2] = {
    {1200, 200}, {1000, 220}, {800, 240}, {600, 260}, {400, 280}
};

// Emoção - Ansiedade
const int anxiety_tones[][2] = {
    {3000, 30}, {2200, 40}, {2800, 35}, {2500, 25}, 
    {3100, 20}, {2700, 50}, {2300, 30}, {2900, 45}
};

// Emoção - Confusão 
const int confusion_tones[][2] = {
    {1800, 70}, {900, 90}, {2500, 80}, {1300, 100}, 
    {2000, 110}, {700, 120}, {2700, 130}, {1600, 140}
};

// Emoção - Calma
const int calm_tones[][2] = {
    {1000, 150}, {1200, 180}, {1400, 200}, {1600, 220}
};

// Emoção - Alerta
const int alert_tones[][2] = {
    {800, 100}, {0, 100}, {800, 100}, {0, 100}, {800, 100}, 
    {0, 100}, {800, 100}, {0, 100}, {800, 100}, {0, 100}
};

class Beeper {
private:

    int buzzerPin;

public:

    Beeper(int pin) {

        buzzerPin = pin;

    }

    void playTone(int frequency, int duration) {

        tone(buzzerPin, frequency, duration);
        delay(duration); 
        noTone(buzzerPin);
        
    }

    void playEmotion(Emotion emotion) {

        const int (*tones)[2];

        switch (emotion) {
            
            case HAPPINESS: {
                tones = happiness_tones;
                break;
            }

            case SADNESS: {
                tones = sadness_tones;
                break;
            }

            case ANXIETY: {
                tones = anxiety_tones;
                break;
            }

            case CONFUSION: {
                tones = confusion_tones;
                break;
            }

            case CALM: {
                tones = calm_tones;
                break;
            }

            case ALERT: {
                tones = alert_tones;
                break;
            }
        
            default: break;
        }

        int numTones = sizeof(happiness_tones) / sizeof(happiness_tones[0]);

        for (int i = 0; i < numTones; i++) {
            playTone(tones[i][0], tones[i][1]);
        }

    }

};

#endif /* _BEEPER_H */
