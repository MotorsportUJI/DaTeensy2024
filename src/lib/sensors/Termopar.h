#ifndef Termopar_SENSOR_H
#define Termopar_SENSOR_H

#include <MAX6675.h>
#include "lib/Controller/SPIMux/SPIMux.h"

class Termopar
{
public:
    Termopar(int sckPin, int csPin, int soPin, SPIMux *mux, int muxIndex);

    float readTemperature();

private:
    uint8_t sckPin;
    uint8_t csPin;
    uint8_t soPin;
    MAX6675 max6675;

    SPIMux *_mux;
    int muxIndex;
};

#endif // Termopar_SENSOR_H
