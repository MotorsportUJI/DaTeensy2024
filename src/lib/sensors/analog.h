#ifndef ANALOGSENSOR
#define ANALOGSENSOR

#include <Arduino.h>

namespace ANALOG
{
    float int2voltage(int value);
    float int2pressurefuel(int value);
    float readSuspension(int pin);
    float sensorToBars(int pin, int minSensorValue, int maxSensorValue, float minBarValue, float maxBarValue);
}

#endif