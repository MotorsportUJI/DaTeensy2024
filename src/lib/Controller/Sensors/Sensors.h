#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

enum SensorType
{
    PRESSURE,
    DISTANCE,
    MAPPING,
    SUSPENSION,
    TEMPERATURE,
    ONOFF
};

class Sensor
{
public:
    Sensor(const char *name, SensorType type, int pin, const char *unit, const char *screenID = NULL, bool sendScreen = false);
    Sensor(const char *name, SensorType type, int pin, float min, float max, float convertedMin, float convertedMax, const char *unit, const char *screenID = NULL, bool sendScreen = false);
    Sensor(const char *name, SensorType type, float (*readFunc)(), const char *unit, const char *screenID = NULL, bool sendScreen = false);
    Sensor(const char *name, SensorType type, float (*readFunc)(), float min, float max, float convertedMin, float convertedMax, const char *unit, const char *screenID = NULL, bool sendScreen = false);
    Sensor(const char *name, SensorType type, float (*readFunc)(), void (*getFunc)(), const char *unit, const char *screenID = NULL, bool sendScreen = false);

    // inicializa los sensores conectados a la teensy y no unsn protocolos o ADC
    void init();
    // lee el sensor y lo convierte a la unidad deseada
    float read();
    // lee el sensor y devuelve el valor sin convertir
    float readRaw();
    // devuelve el nombre del sensor y su valor con unidad
    String Sensor::readFull();
    // devuelve el valor para el obd
    String Sensor::getScreenValue();
    // devuelve el tipo de sensor
    SensorType getType();
    // convierte el valor segun la clase
    float Sensor::convertValue(float value);

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

    // OBD
    const char *screenID;
    bool sendScreen;
};

#endif
