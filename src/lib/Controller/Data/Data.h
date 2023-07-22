#ifndef DATA_H
#define DATA_H

#include "lib/Controller/Telemetry/Telemetry.h"
#include "lib/Controller/SD/SDstore.h"
#include "lib/Controller/Sensors/Sensors.h"
#include "lib/CAN/OBD2.h"

const int MAX_SENSORS = 30; // Máximo número de sensores que puede almacenar

class Data
{
public:
    // Constructor;
    Data::Data(unsigned long intervalValue, TELEMETRY telemetryObj, SDStore sdstoreObj);
    // Add sensor to logger or data collector
    void addSensor(Sensor *sensor);
    // Get all data from all sensors
    String get();
    // Get raw data from all sensors
    String getRaw();
    // Get converted with extension
    String getFull();
    // Do something in iteration
    void loop();

private:
    TELEMETRY telemetry;
    SDStore sdstore;
    Sensor *sensors[MAX_SENSORS];
    int numSensors;
    unsigned long previousMillis;
    unsigned long interval;
};

#endif
