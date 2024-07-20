#ifndef GEARSENSOR_H
#define GEARSENSOR_H

#include <Arduino.h>
#include "lib/Controller/MUX/CD74HC4067SM96.h"

namespace GEAR
{
    void initGear(CD74HC4067SM96 *mux);
    float getGear();

    uint8_t getDesiredGear(); // desired gear = 128 to clone real gear
    void setDesiredGear(uint8_t gear);

    extern CD74HC4067SM96* _muxGear;  // Declare as extern
}

#endif // GEARSENSOR_H
