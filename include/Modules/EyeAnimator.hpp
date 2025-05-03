#ifndef EYE_ANIMATOR_HPP
#define EYE_ANIMATOR_HPP

#include <stdint.h>

class EyeAnimator {
public:
    void drawEyes();

    // Expressões vetoriais
    private drawHappyExpression();
    private drawSadExpression();
    private drawUpsetExpression();
    private drawWonderExpression();
    private drawNormalExpression();
    private drawCloseExpression();
    
    // Controle de estado
    static unsigned long lastBlinkTime;
    static bool blinkState;

    Emotion currentEmotion;
    bool useVectorEyes = true;
};

#endif // EYE_ANIMATOR_HPP
