#pragma once

#include <Arduino.h>
#include "lib/CAN/OBD2.h"
#include "lib/CAN/Conversions.h"
#include "lib/persistence/persistance.h"
#include "lib/Controller/Sensors/Sensors.h"

#include "lib/sensors/analog.h"

class Display
{
public:
    Display(HardwareSerialIMXRT &_serial); // Constructor

    void init();
    void rpmled(int nleds);
    void rpmledInverse(int nleds);

    // data send
    void sendSensorData(Sensor &sensor);
    void sendGear(int str, bool desired = false);
    void sendFuelSystemStatus(int str);
    void sendTimeEngineOn(uint32_t str);

    void endMessage();

    void setMainScreen();
    void setSplashScreen();
    void setDebugScreen();
    void setSensorScreen();

    void sendOBDdata(OBD2::OBD2sensordata OBD2db);

private:
    int ledCount; // Número de LEDs (variable privada)
    HardwareSerialIMXRT *serialScreen;
};