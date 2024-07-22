#include "LED.h"

void LED::init(){

    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.setBrightness(50);
    FastLED.clear();
    for (int i = 0; i < NUM_LEDS; i++){
        Serial.println(i);
        leds[i] = CRGB::Red;
        FastLED.show();
        delay(10);
    }
    delay(1000);
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB::Green;
        FastLED.show();
        delay(10);
    }
    delay(1000);
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB::Blue;
        FastLED.show();
        delay(10);
    }
    _executeFunc = &runRainbow;
}

void LED::rainbow(){
    _executeFunc = &runRainbow;
}

void LED::rainbowWithGlitter() {
    _executeFunc = &runRainbowWithGlitter;
}

// void LED::confetti(){
//     _executeFunc = &runConfetti;
// }

void LED::sinelon() {
    _executeFunc = &runSinelon;
}

void LED::set_line(uint8_t  background_color[3], uint8_t  color[3], int (*valueFunc)()) {
    memcpy(_background_color, background_color, sizeof(_background_color));
    memcpy(_color, color, sizeof(_color));
    
    this->_valueFunc = valueFunc;
    _executeFunc = &runLine;
}

void LED::loop() {
    (this->*_executeFunc)();  
}

void LED::runRainbow() {
    static uint8_t hue = 0;
    fill_rainbow(leds, NUM_LEDS, hue, 7);
    FastLED.show();
    hue++;
    FastLED.delay(20);
}

void LED::runRainbowWithGlitter() {
    static uint8_t hue = 0;
    fill_rainbow(leds, NUM_LEDS, hue, 7);
    // Glitter effect

    if (random8() < 30) {
        leds[random16(NUM_LEDS)] += CRGB::White;
    }
    FastLED.show();
    hue++;
    FastLED.delay(20);
    
}

// void LED::runConfetti() {
    
// }

void LED::runSinelon() {
    static uint8_t gHue = 0;
    fadeToBlackBy(leds, NUM_LEDS, 20);
    int pos = beatsin16(13, 0, NUM_LEDS - 1);
    leds[pos] += CHSV(gHue, 255, 192);
    FastLED.show();
    gHue++;
    FastLED.delay(20);
}

void LED::runLine() {
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB(_background_color[0], _background_color[1], _background_color[2]);
    }
    int value = _valueFunc();
    // int num_leds = map(value, 0, 100, 0, NUM_LEDS);
    for (int i = 0; i < num_leds; i++){
        leds[i] = CRGB(_color[0], _color[1], _color[2]);
    }
}