#ifndef EYE_ANIMATOR_HPP
#define EYE_ANIMATOR_HPP

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Emotion.hpp"
#include "Assets/BitMaps.hpp"
#include "Assets/EyeFrame.hpp"

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT    64
#define EYE_HEIGHT       32
#define OLED_RESET       -1
#define SCREEN_ADDRESS 0x3C

class EyeAnimator {

    private:

        Adafruit_SSD1306 display;
        Emotion currentEmotion;
        unsigned long lastUpdate;
        uint8_t animationFrame;

    public:

        EyeAnimator() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET), 
                    currentEmotion(HAPPINESS), lastUpdate(0), animationFrame(0) {}

        bool begin();

        void setEmotion(Emotion newEmotion);

        void updateAnimation();

    private:

        const EyeFrame& getCurrentFrame();

        uint8_t getFrameCount();

        void drawEyes();

};

#endif /* EYE_ANIMATOR_HPP */