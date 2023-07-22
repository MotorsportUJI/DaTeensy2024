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
        this->screenID = new char[strlen(screenID) + 1];
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
        this->screenID = new char[strlen(screenID) + 1];
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
        this->screenID = new char[strlen(screenID) + 1];
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

String Sensor::getScreenValue()
{
    String data;
    if (!sendScreen)
    {
        return NULL;
    }
    if (readFunc)
    {
        if (getFunc)
        {
            getFunc();
        }
        float value = readFunc(); // If readFunc is not NULL, call the custom read function
        data = String(value);
    }
    else
    {
        int value = Sensor::read();
        data = String(value);
    }

    // ser->printf("oil.txt=\"OFF\"");
    // if sensor y tyupe ONOFF if is true or not null != false send ON else send OFF, if is not defined send OFF
    if (type == ONOFF)
    {
        if (data == "1" || data == "true" || data == "ON" || data == "on" || data != "0" || data != "false" || data != "OFF" || data != "off")
        {
            data = "ON";
        }
        else
        {
            data = "OFF";
        }
    }

    // construct the string to send to the screen
    data = String(screenID) + ".txt=\"" + data + "\"";

    return data;
}

SensorType Sensor::getType()
{
    return type;
}