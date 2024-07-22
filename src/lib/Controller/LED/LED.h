#ifndef LED_CONTROLLER_H_
#define LED_CONTROLLER_H_

#include <Arduino.h>
#include <FastLED.h>
// LEDS
#define NUM_LEDS 60
#define DATA_PIN 5


class LED
{
public:
    void init();
    void rainbow();
    void rainbowWithGlitter();
    // void confetti();
    void sinelon();
    void set_line(uint8_t  background_color[3], uint8_t  color[3], int (*valueFunc)());

    void loop();


private:

    void runRainbow();
    void runRainbowWithGlitter();
    void runConfetti();
    void runSinelon();
    void runLine();


    CRGB leds[NUM_LEDS];
    int num_leds;
    int pin;

    uint8_t  _background_color[3] = {0, 0, 0};
    uint8_t  _color[3] = {0, 0, 0};
    int *_value;
    int (*_valueFunc)() = nullptr; // Callback function pointer

    void(LED::*_executeFunc)() = nullptr; // Callback function pointer

};


#endif // LIB_CONTROLLER_SPIMUX_SPIMUX_H_