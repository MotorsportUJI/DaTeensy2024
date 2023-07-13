#include "max6675_sensor.h"

MAX6675Sensor::MAX6675Sensor(uint8_t sckPin, uint8_t csPin, uint8_t soPin)
    : sckPin(sckPin), csPin(csPin), soPin(soPin), max6675(sckPin, csPin, soPin) {}

float MAX6675Sensor::readTemperature()
{
    return max6675.readCelsius();
}
