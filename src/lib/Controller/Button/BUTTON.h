#ifndef BUTTON_H_
#define BUTTON_H_
#include <Arduino.h>

class BUTTON {
public:
    // Constructor para inicializar el pin del botón
    BUTTON(int pin, std::function<void()> pressAction, unsigned long shortPressMax = 1000)
        : _pin(pin), _pressAction(pressAction), _shortPressMax(shortPressMax),
          _buttonPressed(false), _buttonMs(0) {}

    void init();

    // Actualiza el estado del botón
    void update();

private:
    int _pin;
    std::function<void()> _pressAction;  // Función a ejecutar cuando se presiona el botón
    unsigned long _shortPressMax;
    bool _buttonPressed;
    unsigned long _buttonMs;
};

#endif // BUTTON_H_
