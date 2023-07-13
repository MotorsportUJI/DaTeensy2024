#ifndef MAX6675_SENSOR_H
#define MAX6675_SENSOR_H

#include <MAX6675.h>

class MAX6675Sensor
{
public:
    MAX6675Sensor(uint8_t sckPin, uint8_t csPin, uint8_t soPin);

    float readTemperature();

private:
    uint8_t sckPin;
    uint8_t csPin;
    uint8_t soPin;
    MAX6675 max6675;
};

#endif // MAX6675_SENSOR_H
