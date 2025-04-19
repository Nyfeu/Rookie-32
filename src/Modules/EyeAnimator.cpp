#include "Modules/EyeAnimator.hpp"

bool EyeAnimator::begin() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) return false;
    display.clearDisplay();
    return true;
}

void EyeAnimator::setEmotion(Emotion newEmotion) {
    if(newEmotion != currentEmotion) {
        currentEmotion = newEmotion;
        animationFrame = 0;
        lastUpdate = millis();
        updateAnimation();
    }
}

void EyeAnimator::updateAnimation() {
    if(millis() - lastUpdate < getCurrentFrame().duration) return;
    animationFrame = (animationFrame + 1) % getFrameCount();
    lastUpdate = millis();
    drawEyes();
}

const EyeFrame& EyeAnimator::getCurrentFrame() {
    switch(currentEmotion) {
        case HAPPINESS: return happyFrames[animationFrame];
        case CALM: return calmFrame[animationFrame];
        case SADNESS: return sadnessFrame[animationFrame];
        case ALERT: return nerdFrame[animationFrame];
        // Adicione casos para outras emoções
        default: return happyFrames[0];
    }
}

uint8_t EyeAnimator::getFrameCount() {
    switch(currentEmotion) {
        case HAPPINESS: return sizeof(happyFrames)/sizeof(EyeFrame);
        case CALM: return sizeof(calmFrame)/sizeof(EyeFrame);
        case SADNESS: return sizeof(sadnessFrame)/sizeof(EyeFrame);
        case ALERT: return sizeof(nerdFrame)/sizeof(EyeFrame);
        // Adicionar outras emoções
        default: return 1;
    }
}

void EyeAnimator::drawEyes() {

    display.clearDisplay();
    EyeFrame frame = getCurrentFrame();
    
    if (frame.singleImage) {

        uint8_t posX = (SCREEN_WIDTH - frame.width) / 2;
        uint8_t posY = (SCREEN_HEIGHT - frame.height) / 2;
        display.drawBitmap(posX, posY, frame.leftEye, frame.width, frame.height, SSD1306_WHITE);

    } else {

        // Calcula posições centralizadas
        const uint8_t EYE_GAP = 16;  // Espaço entre os olhos (8 pixels)
        const uint8_t EYE_WIDTH = frame.width;
        
        // Posição horizontal
        uint8_t totalWidth = (2 * EYE_WIDTH) + EYE_GAP;
        uint8_t startX = (SCREEN_WIDTH - totalWidth) / 2;
        
        // Posição vertical (centralizado)
        uint8_t eyeY = (SCREEN_HEIGHT - frame.height) / 2;
    
        // Desenha os olhos
        display.drawBitmap(startX, eyeY, frame.leftEye, EYE_WIDTH, frame.height, SSD1306_WHITE);
        display.drawBitmap(startX + EYE_WIDTH + EYE_GAP, eyeY, frame.rightEye, EYE_WIDTH, frame.height, SSD1306_WHITE);
    
    }

    display.display();

}