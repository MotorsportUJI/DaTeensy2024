#include "button.h"

void BUTTON::init() {
        pinMode(_pin, INPUT);
    }

void BUTTON::update() {
        bool currentState = digitalRead(_pin) == LOW;
        if (currentState && !_buttonPressed) {
            _buttonMs = millis();
            _buttonPressed = true;
        } else if (!currentState && _buttonPressed) {
            if (millis() - _buttonMs < _shortPressMax) {
                _pressAction();
            }
            _buttonPressed = false;
        }
    }