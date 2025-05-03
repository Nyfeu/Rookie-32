#include "Modules/EyeAnimator.hpp"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display; // Deve ser inicializado fora deste arquivo

// Estado interno para animações vetoriais
static int q = -15;
static bool happy_state = false;
static const int skip = 1;

// Para piscada automática
unsigned long EyeAnimator::lastBlinkTime = 0;
bool EyeAnimator::blinkState = false;

Emotion currentEmotion;
bool useVectorEyes = true;

void EyeAnimator::drawHappyExpression() {
    for (int i = 62 * skip; i > 58; i -= 1) {
        display.clearDisplay();
        display.fillRoundRect(8, 12, 50, 35, 11, SSD1306_WHITE);
        display.fillRoundRect(70, 12, 50, 35, 11, SSD1306_WHITE);
        display.fillCircle(33, i, 38, SSD1306_BLACK);
        display.fillCircle(95, i, 38, SSD1306_BLACK);
        display.display();
    }
}

void EyeAnimator::drawSadExpression() {
    for (int i = 0; i <= 15; i += 3) {
        display.clearDisplay();
        display.fillRoundRect(8, 18, 50, 29, 9, SSD1306_WHITE);
        display.fillRoundRect(70, 18, 50, 29, 9, SSD1306_WHITE);
        display.fillTriangle(3, 14, 64, 14, 3, 21 + i, SSD1306_BLACK);
        display.fillTriangle(68, 14, 124, 21 + i, 124, 14, SSD1306_BLACK);
        display.display();
    }
}

void EyeAnimator::drawNormalExpression() {
    display.clearDisplay();
    display.fillRoundRect(8, 12, 50, 35, 9, SSD1306_WHITE);
    display.fillRoundRect(70, 12, 50, 35, 9, SSD1306_WHITE);
    display.display();
}

void EyeAnimator::drawCloseExpression() {
    display.clearDisplay();
    display.fillRoundRect(5, 19, 55, 18, 6, SSD1306_WHITE);
    display.fillRoundRect(67, 19, 55, 18, 6, SSD1306_WHITE);
    display.fillRect(5, 1, 55, 18, SSD1306_BLACK);
    display.fillRect(67, 1, 55, 18, SSD1306_BLACK);
    display.display();
}

void EyeAnimator::drawWonderExpression() {
    for (int i = 1; i <= 10 * skip; i += 4) {
        display.clearDisplay();
        display.fillRoundRect(8, 12 + i, 50, 35 - i, 9, SSD1306_WHITE);
        display.fillRoundRect(70, 12, 50, 35, 9, SSD1306_WHITE);
        display.display();
    }
    delay(1600 * skip);
    for (int i = 1; i <= 10 * skip; i += 4) {
        display.clearDisplay();
        display.fillRoundRect(8, 22 - i, 50, 25 + i, 9, SSD1306_WHITE);
        display.fillRoundRect(70, 12 + i, 50, 35 - i, 9, SSD1306_WHITE);
        display.display();
    }
    delay(1600 * skip);
}

void EyeAnimator::drawUpsetExpression() {
    if (!happy_state) {
        display.clearDisplay();
        display.drawRoundRect(8, 12, 50, 35, 9, SSD1306_WHITE);
        display.drawRoundRect(70, 12, 50, 35, 9, SSD1306_WHITE);
        display.fillRect(8, q, 50, 35, SSD1306_BLACK);
        display.fillRect(70, q, 50, 35, SSD1306_BLACK);
        display.display();
        if (q <= -7) q += 3;
    }
}

void EyeAnimator::drawEyes() {
    // Somente modo vetorial (Akno)
    switch(currentEmotion) {
        case HAPPINESS: drawHappyExpression(); break;
        case SADNESS: drawSadExpression(); break;
        case CALM:
            long now = millis();
            if (!blinkState && (now - lastBlinkTime > 3700)) {
            drawCloseExpression();         // Pisca
            blinkState = true;
            lastBlinkTime = now;
            } else if (blinkState && (now - lastBlinkTime > 150)) {
            drawNormalExpression();        // Abre rapidamente
            blinkState = false;
            lastBlinkTime = now;
            }
            break;
        case ALERT: drawWonderExpression(); break;
        case ANXIETY: drawUpsetExpression(); break;
        default: drawNormalExpression(); break;
    }
}
