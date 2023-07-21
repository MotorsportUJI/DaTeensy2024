#include "Sensors.h"

Sensor::Sensor(const char *name, SensorType type, int pin)
{
    this->name = name;
    this->type = type;
    this->pin = pin;
    this->min = 0.0;
    this->max = 5.0;
    this->convertedMin = 0.0;
    this->convertedMax = 1023.0;
    this->unit = "";
    this->readFunc = NULL; // Initialize readFunc as NULL
    this->getFunc = NULL;  // Initialize getFunc as NULL
}

Sensor::Sensor(const char *name, SensorType type, int pin, float min, float max, float convertedMin, float convertedMax, const char *unit)
{
    this->name = name;
    this->type = type;
    this->pin = pin;
    this->min = min;
    this->max = max;
    this->convertedMin = convertedMin;
    this->convertedMax = convertedMax;
    this->unit = unit;
    this->readFunc = NULL; // Initialize readFunc as NULL
    this->getFunc = NULL;  // Initialize getFunc as NULL
}

Sensor::Sensor(const char *name, SensorType type, float (*readFunc)(), const char *unit)
{
    this->name = name;
    this->type = type;
    this->pin = 0;
    this->min = 0.0;
    this->max = 5.0;
    this->convertedMin = 0.0;
    this->convertedMax = 1023.0;
    this->unit = unit;
    this->readFunc = readFunc; // Assign the custom read function
    this->getFunc = NULL;      // Initialize getFunc as NULL
}

Sensor::Sensor(const char *name, SensorType type, float (*readFunc)(), void (*getFunc)(), const char *unit)
{
    this->name = name;
    this->type = type;
    this->pin = 0;
    this->min = 0.0;
    this->max = 5.0;
    this->convertedMin = 0.0;
    this->convertedMax = 1023.0;
    this->unit = unit;
    this->readFunc = readFunc; // Assign the custom read function
    this->getFunc = getFunc;   // Assign the custom get function
}

void Sensor::init()
{
    pinMode(pin, INPUT);
}

float Sensor::read()
{
    if (readFunc)
    {
        if (getFunc)
        {
            getFunc();
        }
        return readFunc(); // If readFunc is not NULL, call the custom read function
    }
    else
    {
        int rawValue = analogRead(pin);
        return map(rawValue, 0, 1023, convertedMin, convertedMax);
    }
}

float Sensor::readRaw()
{
    if (readFunc)
    {
        if (getFunc)
        {
            getFunc();
        }
        return readFunc(); // If readFunc is not NULL, call the custom read function
    }
    else
    {
        return analogRead(pin);
    }
}

String Sensor::readFull()
{
    String data;
    if (readFunc)
    {
        if (getFunc)
        {
            getFunc();
        }
        float value = readFunc(); // If readFunc is not NULL, call the custom read function
        data = String(value) + " " + String(unit);
    }
    else
    {
        int value = Sensor::read();
        data = String(value) + " " + String(unit);
    }

    return data;
}
