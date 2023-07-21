#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

enum SensorType
{
    PRESSURE,
    DISTANCE,
    MAPPING,
    SUSPENSION,
    TEMPERATURE
};

class Sensor
{
public:
    Sensor(const char *name, SensorType type, int pin);
    Sensor(const char *name, SensorType type, int pin, float min, float max, float convertedMin, float convertedMax, const char *unit);
    Sensor(const char *name, SensorType type, float (*readFunc)(), const char *unit);
    Sensor(const char *name, SensorType type, float (*readFunc)(), void (*getFunc)(), const char *unit);

    // inicializa los sensores conectados a la teensy y no unsn protocolos o ADC
    void init();
    // lee el sensor y lo convierte a la unidad deseada
    float read();
    // lee el sensor y devuelve el valor sin convertir
    float readRaw();
    // devuelve el nombre del sensor y su valor con unidad
    String Sensor::readFull();

private:
    const char *name;
    SensorType type;
    int pin;
    float min;
    float max;
    float convertedMin;
    float convertedMax;
    const char *unit;
    void (*getFunc)();
    float (*readFunc)();
};

#endif
