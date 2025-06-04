#include "Modules/Beeper.hpp"

namespace {

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
        {2500, 80}, {2800, 100}, {2200, 70}, {3000, 90}, {2600, 60}
    };

    // Emoção - Alerta
    const int alert_tones[][2] = {
        {800, 100}, {0, 100}, {800, 100}, {0, 100}, {800, 100}, 
        {0, 100}, {800, 100}, {0, 100}, {800, 100}, {0, 100}
    };

}

// Implementação do playTone
void Beeper::playTone(int frequency, int duration) {
    tone(buzzerPin, frequency, duration);
    vTaskDelay(pdMS_TO_TICKS(duration));   // Libera a CPU para outras tasks durante o tempo do beep
    noTone(buzzerPin);
}

void Beeper::playEmotion(Emotion emotion) {
    const int (*tones)[2];
    int numTones = 0;

    switch (emotion) {
        case HAPPINESS:
            tones = happiness_tones;
            numTones = sizeof(happiness_tones) / sizeof(happiness_tones[0]);
            break;
        case SADNESS:
            tones = sadness_tones;
            numTones = sizeof(sadness_tones) / sizeof(sadness_tones[0]);
            break;
        case ANXIETY:
            tones = anxiety_tones;
            numTones = sizeof(anxiety_tones) / sizeof(anxiety_tones[0]);
            break;
        case CONFUSION:
            tones = confusion_tones;
            numTones = sizeof(confusion_tones) / sizeof(confusion_tones[0]);
            break;
        case CALM:
            tones = calm_tones;
            numTones = sizeof(calm_tones) / sizeof(calm_tones[0]);
            break;
        case ALERT:
            tones = alert_tones;
            numTones = sizeof(alert_tones) / sizeof(alert_tones[0]);
            break;
        default:
            return;
    }

    for (int i = 0; i < numTones; i++) {
        playTone(tones[i][0], tones[i][1]);
    }
}
