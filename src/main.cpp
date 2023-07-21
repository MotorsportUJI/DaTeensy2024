#include <Arduino.h>
#include "settings.h"

#include "lib/CAN/OBD2.h"

#include "lib/persistence/persistance.h"
#include "lib/Controller/SD/SDstore.h"

#include "lib/SteeringWheel/SteeringWheel.h"
#include "lib/Controller/Telemetry/Telemetry.h"
#include "lib/Controller/Sensors/Sensors.h"
#include "lib/Controller/Data/Data.h"

#include "lib/sensors/gear.h"
#include "lib/sensors/buttons.h"

// Gyro sensor
#include "lib/sensors/GY-6500.h"

// Termopar snesor
#include "lib/sensors/max6675_sensor.h"

// Settings pin found in settings.h
OBD2::OBD2sensordata OBD2db = {0};

// Telemetry object
TELEMETRY telemetry(TelemetryUART);
SDStore sdstore;

GY6500Sensor axis6(DEVICE_ADDRESS, ALPHA, DT);
MAX6675Sensor max6675(SCK_PIN, CS_PIN, SO_PIN);

// Sensors
Sensor FuelPressure("Presion gasolina", PRESSURE, FUEL_PRESSURE_PIN, FUEL_PRESSURE_MIN, FUEL_PRESSURE_MAX, FUEL_PRESSURE_MIN_BAR, FUEL_PRESSURE_MAX_BAR, "bar");
Sensor OilPressure("Presion aceite", PRESSURE, OIL_PRESSURE_PIN, OIL_PRESSURE_MIN, OIL_PRESSURE_MAX, OIL_PRESSURE_MIN_BAR, OIL_PRESSURE_MAX_BAR, "bar");

Sensor SuspensionFrontRight("Suspension delantera derecha", SUSPENSION, SUSPENSION_FRONT_RIGHT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm");
Sensor SuspensionFrontLeft("Suspension delantera izquierda", SUSPENSION, SUSPENSION_FRONT_LEFT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm");
Sensor SuspensionRearRight("Suspension trasera derecha", SUSPENSION, SUSPENSION_REAR_RIGHT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm");
Sensor SuspensionRearLeft("Suspension trasera izquierda", SUSPENSION, SUSPENSION_REAR_LEFT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm");

Sensor Firewall("Firewall", TEMPERATURE, max6675.readTemperature());

// Sensor GyroAngle("Gyro Angulo", MAPPING, axis6.getAngle(), "º");
// Sensor GyroSpeed("Gyro Velocidad", MAPPING, axis6.getSpeed(), "º/s");

// Controlador de datos
Data dataManager(200, telemetry, sdstore);

// Dash info
uint32_t time_engine_on = 0;

uint32_t elapsed_minute = 0;
uint32_t elapsed_second = 0;
uint32_t elapsed_200ms = 0;
uint32_t elapsed_100ms = 0;
uint32_t elapsed_50ms = 0;

boolean previous_contact = false;
boolean previous_fss = false;

// IntervalTimer EmulateDashTimer;

void setup()
{

// init serial
#ifdef DEBUG
    Serial.begin(115200);
#endif

    // EmulateDashTimer.priority(255);
    // EmulateDashTimer.begin(emulateDash, 100000);

    // Init sensors
    FuelPressure.init();
    OilPressure.init();
    SuspensionFrontRight.init();
    SuspensionFrontLeft.init();
    SuspensionRearRight.init();
    SuspensionRearLeft.init();

    // Add sensors to data manager
    dataManager.addSensor(&FuelPressure);
    dataManager.addSensor(&OilPressure);
    dataManager.addSensor(&SuspensionFrontRight);
    dataManager.addSensor(&SuspensionFrontLeft);
    dataManager.addSensor(&SuspensionRearRight);
    dataManager.addSensor(&SuspensionRearLeft);
    dataManager.addSensor(&Firewall);
    // dataManager.addSensor(&GyroAngle);
    // dataManager.addSensor(&GyroSpeed);

    DISPLAYY::initScreen(ScreenUART);

    initOBD2(OBD2db);

    GEAR::initGear();

    DISPLAYY::rpmled(0);
    OBD2db.engine_rpmA = 0;
    OBD2db.engine_rpmB = 0;

    BUTTONS::initButtons();

    pinMode(DEBUG_LED, OUTPUT);
    delay(1000);
    DISPLAYY::setMainScreen();

    axis6.begin();
}

void loop()
{

    OBD2::OBD2events();
    BUTTONS::checkButtons();

    if (millis() - elapsed_50ms > 50)
    {

        BUTTONS::checkButtons();

        elapsed_50ms = millis();
    }
    // execute each 100ms
    if (millis() - elapsed_100ms > 100)
    {

        // updateScreen
        DISPLAYY::sendOBDdata(OBD2db);
        DISPLAYY::sendGear(GEAR::getGear());

        DISPLAYY::sendOil(OilPressure.read());

        DISPLAYY::sendTimeEngineOn(time_engine_on);

        DISPLAYY::sendFuelPressure(analogRead(15));

        // emulateDash
        if (GEAR::getDesiredGear() != 128)
        {
            OBD2::emulateDash(GEAR::getDesiredGear());
        }
        else
        {
            OBD2::emulateDash(GEAR::getGear());
        }

        // print data to sd
        dataManager.loop();

        elapsed_100ms = millis();
    }

    if (millis() - elapsed_200ms > 200)
    {

        elapsed_200ms = millis();
    }

    // execute each second
    if (millis() - elapsed_second > 1000)
    {
        time_engine_on = (OBD2db.fuel_system_status != 0) ? time_engine_on + 1 : 0;
    }

    // execute each minute
    if (millis() - elapsed_minute > 60 * 1000)
    {

        // increase time alive counter
        PERSISTANCE::increaseTimeCounter(EEPROM_time_base_address);
        // increase engine on time

        if (OBD2db.fuel_system_status != 0)
        {
            if (previous_fss)
            {
                PERSISTANCE::increaseTimeCounter(EEPROM_fss_base_address);
            }
            previous_fss = true;
        }
        else
        {
            previous_fss = false;
        }

        elapsed_minute = millis();
    }
}