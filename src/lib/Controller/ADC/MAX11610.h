#ifndef MAX11610_H
#define MAX11610_H

#include <Arduino.h>
#include <Wire.h>

class MAX11610
{
public:
    MAX11610();
    uint16_t readADC(uint8_t channel);

private:
    uint8_t _address;

    void writeRegister(uint8_t reg, uint8_t value);
    uint16_t readRegister(uint8_t reg);
};

#endif
