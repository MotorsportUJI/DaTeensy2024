#ifndef MAX11610_H
#define MAX11610_H

#include <Arduino.h>
#include <Wire.h>
#include "lib/Controller/I2CMux/TCA9548A.h"

class MAX11610
{
public:
    MAX11610(uint8_t address, int I2CPort, TCA9548A *tca);
    uint16_t readADC(uint8_t channel);
    int readADC0();
    int readADC1();
    int readADC2();
    int readADC3();
    int readADC4();
    int readADC5();
    int readADC6();
    int readADC7();
    int readADC8();
    int readADC9();
    int readADC10();


private:
    uint8_t _address;
    int _I2CPORT =0;
    TCA9548A *_tca;

    void writeRegister(uint8_t reg, uint8_t value);
    uint16_t readRegister(uint8_t reg);
};

#endif
