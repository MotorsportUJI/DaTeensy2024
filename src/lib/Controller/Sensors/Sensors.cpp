#include "Sensors.h"

Sensor::Sensor(const char *name, SensorType type, int pin, const char *unit, const char *screenID = NULL, bool sendScreen = false)
{
    this->name = name;
    this->type = type;
    this->pin = pin;
    this->min = 0.0;
    this->max = 5.0;
    this->convertedMin = 0.0;
    this->convertedMax = 1023.0;
    this->unit = unit;
    this->readFunc = NULL; // Initialize readFunc as NULL
    this->getFunc = NULL;  // Initialize getFunc as NULL

    // If screenID is not NULL, copy the string to the screenID attribute
    if (screenID)
    {
        this->screenID = screenID;
        this->sendScreen = sendScreen;
    }
    else
    {
        this->screenID = NULL;
    }
}

Sensor::Sensor(const char *name, SensorType type, int pin, float min, float max, float convertedMin, float convertedMax, const char *unit, const char *screenID = NULL, bool sendScreen = false)
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
    // If screenID is not NULL, copy the string to the screenID attribute
    if (screenID)
    {
        this->screenID = screenID;
        this->sendScreen = sendScreen;
    }
    else
    {
        this->screenID = NULL;
    }
}

Sensor::Sensor(const char *name, SensorType type, float (*readFunc)(), const char *unit, const char *screenID = NULL, bool sendScreen = false)
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
    // If screenID is not NULL, copy the string to the screenID attribute
    if (screenID)
    {
        this->screenID = screenID;
        this->sendScreen = sendScreen;
    }
    else
    {
        this->screenID = NULL;
    }
}

Sensor::Sensor(const char *name, SensorType type, float (*readFunc)(), float min, float max, float convertedMin, float convertedMax, const char *unit, const char *screenID = NULL, bool sendScreen = false)
{
    this->name = name;
    this->type = type;
    this->pin = 0;
    this->min = min;
    this->max = max;
    this->convertedMin = convertedMin;
    this->convertedMax = convertedMax;
    this->unit = unit;
    this->readFunc = readFunc; // Assign the custom read function
    this->getFunc = NULL;      // Initialize getFunc as NULL
    // If screenID is not NULL, copy the string to the screenID attribute
    if (screenID)
    {
        this->screenID = screenID;
        this->sendScreen = sendScreen;
    }
    else
    {
        this->screenID = NULL;
    }
}

Sensor::Sensor(const char *name, SensorType type, float (*readFunc)(), void (*getFunc)(), const char *unit, const char *screenID = NULL, bool sendScreen = false)
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

    // If screenID is not NULL, copy the string to the screenID attribute
    if (screenID)
    {
        this->screenID = new char[strlen(screenID) + 1];
        this->sendScreen = sendScreen;
    }
    else
    {
        this->screenID = NULL;
    }
}

void Sensor::init()
{
    pinMode(pin, INPUT);
}

float Sensor::read()
{
    int rawValue;

    if (readFunc)
    {
        if (getFunc)
        {
            getFunc();
        }
        // si es tipo maping devolver el valor mapeado
        if (type == SensorType::MAPPING)
        {
            rawValue = readFunc();
        }
    }
    else
    {
        rawValue = analogRead(pin);
    }
    return convertValue(rawValue);
}

float Sensor::readRaw()
{
    if (readFunc)
    {
        if (getFunc)
        {
            getFunc();
        }
        return (readFunc()); // If readFunc is not NULL, call the custom read function
    }
    else
    {
        return (analogRead(pin));
    }
}

String Sensor::readFull()
{
    String data;
    float value = Sensor::read();
    data = String(name) + ": " + String(value) + " " + String(unit);

    return data;
}

String Sensor::getScreenValue()
{
    String data;
    if (!sendScreen)
    {
        return NULL;
    }

    float value = Sensor::read();
    data = String(value);

    // construct the string to send to the screen
    data = String(screenID) + ".txt=\"" + data + "\"";

    return data;
}

SensorType Sensor::getType()
{
    return type;
}

float Sensor::convertValue(float value)
{
    if (type == SensorType::MAPPING)
    {
        value = map(value, min, max, convertedMin, convertedMax);
    }
    else if (type == SensorType::ONOFF)
    {
        if (value == 1 || value == true || value != 0 || value != false)
        {
            value = 1;
        }
        else
        {
            value = 0;
        }
    }

    return value;
}