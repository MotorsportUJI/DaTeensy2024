#ifndef DATA_H
#define DATA_H

#include "lib/Controller/Telemetry/Telemetry.h"
#include "lib/Controller/SD/SDStore.h"
#include "lib/Controller/Sensors/Sensors.h"
#include "lib/CAN/OBD2.h"
#include "lib/Screen/Screen.h"

const int MAX_SENSORS = 35; // Máximo número de sensores que puede almacenar

class Data
{
public:
    // Constructor;
    Data(unsigned long intervalValue, HardwareSerial &telemetryUART, Display *displayObj);

    // init
    void init();

    // Add sensor to logger or data collector
    void addSensor(Sensor *sensor);

    // Get all data from all sensors
    String get();

    // Get the data to send via telemetry
    String getTelemetry();

    // Get raw data from all sensors
    String getRaw();

    // Get converted with extension
    String getFull();

    // Do something in iteration
    void loop();

    boolean debug = false;
    boolean debugTelemetry = true;

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
