#ifndef ANALOGSENSOR
#define ANALOGSENSOR

#include <Arduino.h>

namespace ANALOG
{
    float int2voltage(int value);
    float int2pressurefuel(int value);

}

#endif