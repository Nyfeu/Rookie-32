#include "Modules/EyeAnimator.hpp"

// Inicializa o display OLED e limpa a tela
bool EyeAnimator::begin() {

    // Tenta iniciar o display; se falhar, retorna false
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) return false;

    // Limpa qualquer conteúdo anterior
    display.clearDisplay(); 

    // Retorna true se a inicialização for bem-sucedida
    return true;

}

// Altera a emoção atual do olho e reinicia a animação correspondente
void EyeAnimator::setEmotion(Emotion newEmotion) {

    // Só muda se a emoção for diferente da atual
    if(newEmotion != currentEmotion) {

        currentEmotion = newEmotion;
        animationFrame = 0;            // Reinicia o índice do quadro da animação
        lastUpdate = millis();         // Armazena o tempo atual
        updateAnimation();

    }
}

void EyeAnimator::updateAnimation() {

    // Espera o tempo de exibição do quadro atual antes de atualizar
    if(millis() - lastUpdate < getCurrentFrame().duration) return;

    // Avança para o próximo quadro, voltando ao início se necessário
    animationFrame = (animationFrame + 1) % getFrameCount();

    // Atualiza o tempo do último quadro
    lastUpdate = millis();

    // Redesenha os olhos com o novo quadro
    drawEyes();

}

const EyeFrame& EyeAnimator::getCurrentFrame() {
    switch(currentEmotion) {
        case HAPPINESS: return happyFrames[animationFrame];
        case CALM: return calmFrame[animationFrame];
        case SADNESS: return sadnessFrame[animationFrame];
        case ALERT: return alertFrame[animationFrame];
        // Adicionar casos para outras emoções
        default: return happyFrames[0];
    }
}

uint8_t EyeAnimator::getFrameCount() {
    switch(currentEmotion) {
        case HAPPINESS: return sizeof(happyFrames)/sizeof(EyeFrame);
        case CALM: return sizeof(calmFrame)/sizeof(EyeFrame);
        case SADNESS: return sizeof(sadnessFrame)/sizeof(EyeFrame);
        case ALERT: return sizeof(alertFrame)/sizeof(EyeFrame);
        // Adicionar outras emoções
        default: return 1;
    }
}

void EyeAnimator::drawEyes() {

    // Limpa o conteúdo anterior do display
    display.clearDisplay();

    // Obtém o quadro atual da animação
    EyeFrame frame = getCurrentFrame();
    
    if (frame.singleImage) {

        // Se o quadro contém apenas uma imagem (sem olho esquerdo/direito separados)

        uint8_t posX = (SCREEN_WIDTH - frame.width) / 2;     // Centraliza horizontalmente
        uint8_t posY = (SCREEN_HEIGHT - frame.height) / 2;   // Centraliza verticalmente

        // Desenha a imagem no display OLED inteiro
        display.drawBitmap(posX, posY, frame.leftEye, frame.width, frame.height, SSD1306_WHITE);

    } else {

        // Se o quadro contém dois olhos separados (esquerdo e direito)

        // Calcula posições centralizadas
        const uint8_t EYE_GAP = 16;                          // Espaço entre os olhos
        const uint8_t EYE_WIDTH = frame.width;
        
        // Posição horizontal (centralizado)
        // Calcula a largura total (olho esquerdo + espaço + olho direito)
        uint8_t totalWidth = (2 * EYE_WIDTH) + EYE_GAP;
        uint8_t startX = (SCREEN_WIDTH - totalWidth) / 2;
        
        // Posição vertical (centralizado)
        uint8_t eyeY = (SCREEN_HEIGHT - frame.height) / 2;
    
        // Desenha os olhos
        display.drawBitmap(startX, eyeY, frame.leftEye, EYE_WIDTH, frame.height, SSD1306_WHITE);
        display.drawBitmap(startX + EYE_WIDTH + EYE_GAP, eyeY, frame.rightEye, EYE_WIDTH, frame.height, SSD1306_WHITE);
    
    }

    // Atualiza o display com os desenhos
    display.display();

}