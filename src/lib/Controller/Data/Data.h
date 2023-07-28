#ifndef DATA_H
#define DATA_H

#include "lib/Controller/Telemetry/Telemetry.h"
#include "lib/Controller/SD/SDstore.h"
#include "lib/Controller/Sensors/Sensors.h"
#include "lib/CAN/OBD2.h"
#include "lib/SteeringWheel/SteeringWheel.h"

const int MAX_SENSORS = 30; // Máximo número de sensores que puede almacenar

class Data
{
public:
    // Constructor;
    Data(unsigned long intervalValue, TELEMETRY telemetryObj, SDStore sdstoreObj, Display *display);
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

    boolean debug = false;

private:
    TELEMETRY telemetry;
    SDStore sdstore;
    Sensor *sensors[MAX_SENSORS];
    Display *display;
    int numSensors;
    unsigned long previousMillis;
    unsigned long interval;
};

#endif
