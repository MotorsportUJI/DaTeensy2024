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

// Gyro sensor
#include "lib/sensors/GY-6500.h"

// Termopar snesor
#include "lib/sensors/max6675_sensor.h"

// Settings pin found in settings.h
OBD2::OBD2sensordata OBD2db = {0};

// Display object
Display display(ScreenUART);
int CURRENT_SCREEN = 0;

// Telemetry object
TELEMETRY telemetry(TelemetryUART);
SDStore sdstore;

GY6500Sensor axis6(DEVICE_ADDRESS, ALPHA, DT);
MAX6675Sensor max6675(SCK_PIN, CS_PIN, SO_PIN);

// Sensors
Sensor FuelPressure("Presion gasolina", PRESSURE, FUEL_PRESSURE_PIN, FUEL_PRESSURE_MIN, FUEL_PRESSURE_MAX, FUEL_PRESSURE_MIN_BAR, FUEL_PRESSURE_MAX_BAR, "bar", "fuel_p", true);
Sensor OilPressure("Presion aceite", PRESSURE, OIL_PRESSURE_PIN, OIL_PRESSURE_MIN, OIL_PRESSURE_MAX, OIL_PRESSURE_MIN_BAR, OIL_PRESSURE_MAX_BAR, "bar", "oil_p", true);

Sensor SuspensionFrontRight("Suspension delantera derecha", SUSPENSION, SUSPENSION_FRONT_RIGHT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", "susp_f_r", true);
Sensor SuspensionFrontLeft("Suspension delantera izquierda", SUSPENSION, SUSPENSION_FRONT_LEFT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", "susp_f_l", true);
Sensor SuspensionRearRight("Suspension trasera derecha", SUSPENSION, SUSPENSION_REAR_RIGHT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", "susp_r_r", true);
Sensor SuspensionRearLeft("Suspension trasera izquierda", SUSPENSION, SUSPENSION_REAR_LEFT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", "sus_r_l", true);

Sensor Firewall("Firewall", TEMPERATURE, max6675.readTemperature(), "ºC", "firewall", true);

Sensor GyroAngle("Gyro Angulo", MAPPING, axis6.getAngle(), "º", "gyro_angle", true);
Sensor GyroSpeed("Gyro Velocidad", MAPPING, axis6.getSpeed(), "º/s", "gyro_speed", true);

// gear sensor
Sensor Gear("Gear", MAPPING, GEAR::getGear(), "gear", "gear", true);

// odb sensors

Sensor ODBRpm("RPM", MAPPING, OBD2CONVERSIONS::OBD2RPM(OBD2db), "RPM", "rpm", true);
Sensor ODBCoolantTemp("Temperatura refrigerante", MAPPING, OBD2CONVERSIONS::OBD2TMP(OBD2db.Engine_coolant_temperature), "ºC", "watertemp", true);
Sensor ODBAirTemp("Temperatura aire", MAPPING, OBD2CONVERSIONS::OBD2TMP(OBD2db.intake_air_temperature), "ºC", "airtemp", true);
Sensor ODBThrottle("Acelerador", MAPPING, OBD2CONVERSIONS::OBD2PC(OBD2db.throttle_position), "%", "throttle", true);
Sensor ODBThrottleRel("Acelerador relativo", MAPPING, OBD2CONVERSIONS::OBD2PC(OBD2db.relavite_throttle_position), "%", "throttlerel", true);

Sensor ODBAbsPressure("Presion absoluta", MAPPING, OBD2db.absolute_barometric_presure, "kPa", "abspressure", true);
Sensor ODBIntakePressure("Presion admision", MAPPING, OBD2db.intake_manifold_absolute_pressure, "kPa", "presIntake", true);
Sensor ODBDTCCount("DTC", MAPPING, OBD2db.DTC_CNT, "DTC", "dtc", true);

Sensor ODBVoltage("Voltaje", MAPPING, OBD2CONVERSIONS::OBD2Volt(OBD2db), "V", "voltage", true);
Sensor ODBEngineLoad("Carga motor", MAPPING, OBD2CONVERSIONS::OBD2PC(OBD2db.Calculated_Engine_load), "%", "engineload", true);
// sendFuelSystemStatus(OBD2db.fuel_system_status);

Sensor ODBTrim("Trim", MAPPING, OBD2CONVERSIONS::OBD2Trim(OBD2db.long_term_fuel_trim), "%", "FT", true);
Sensor ODB02Trim("Trim O2", MAPPING, OBD2CONVERSIONS::OBD2Trim(OBD2db.oxygen_sensor_long_term_fuel_trim), "%", "O2trim", true);
Sensor ODB02Volt("Voltaje O2", MAPPING, OBD2CONVERSIONS::OBD2VoltO2(OBD2db.oxygen_sensor_voltage), "V", "O2v", true);

Sensor ODBTimingAdvance("Avance", MAPPING, OBD2CONVERSIONS::OBD2Advance(OBD2db.timing_advance), "º", "Tadv", true);
Sensor ODBSpeed("Velocidad", MAPPING, OBD2db.vehicle_speed, "km/h", "speed", true);

//     sendDesiredGear(GEAR::getDesiredGear());

// Controlador de datos
Data dataManager(200, telemetry, sdstore, &display);

// Dash info
uint32_t time_engine_on = 0;

uint32_t elapsed_minute = 0;
uint32_t elapsed_second = 0;
uint32_t elapsed_200ms = 0;
uint32_t elapsed_100ms = 0;
uint32_t elapsed_50ms = 0;

// button prees ms
uint32_t green_button_ms = 0;
uint32_t red_button_ms = 0;

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

    /**--------------------------------------------
     *               Init sensors
     *---------------------------------------------**/
    FuelPressure.init();
    OilPressure.init();
    SuspensionFrontRight.init();
    SuspensionFrontLeft.init();
    SuspensionRearRight.init();
    SuspensionRearLeft.init();

    /**--------------------------------------------
     *               Initi data logger
     *---------------------------------------------**/

    // Add sensors to data manager
    dataManager.addSensor(&FuelPressure);
    dataManager.addSensor(&OilPressure);
    dataManager.addSensor(&SuspensionFrontRight);
    dataManager.addSensor(&SuspensionFrontLeft);
    dataManager.addSensor(&SuspensionRearRight);
    dataManager.addSensor(&SuspensionRearLeft);
    dataManager.addSensor(&Firewall);
    dataManager.addSensor(&GyroAngle);
    dataManager.addSensor(&GyroSpeed);
    dataManager.addSensor(&Gear);

    // OBD2 sensors data manager
    dataManager.addSensor(&ODBRpm);
    dataManager.addSensor(&ODBCoolantTemp);
    dataManager.addSensor(&ODBAirTemp);
    dataManager.addSensor(&ODBThrottle);
    dataManager.addSensor(&ODBThrottleRel);
    dataManager.addSensor(&ODBIntakePressure);
    dataManager.addSensor(&ODBTrim);
    dataManager.addSensor(&ODB02Trim);
    dataManager.addSensor(&ODB02Volt);
    dataManager.addSensor(&ODBVoltage);
    dataManager.addSensor(&ODBEngineLoad);
    dataManager.addSensor(&ODBTimingAdvance);
    dataManager.addSensor(&ODBSpeed);
    dataManager.addSensor(&ODBAbsPressure);
    dataManager.addSensor(&ODBDTCCount);

    initOBD2(OBD2db);

    GEAR::initGear();
    // Pasa el puntero display

    display.rpmled(0);
    display.setMainScreen();

    OBD2db.engine_rpmA = 0;
    OBD2db.engine_rpmB = 0;

    pinMode(DEBUG_LED, OUTPUT);
    delay(1000);

    axis6.begin();

    // button init
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
    pinMode(RED_BUTTON, INPUT_PULLUP);
}

void loop()
{

    OBD2::OBD2events();

    /**----------------------
     *    check buttons  long or short press
     *------------------------**/
    // green short press
    if (digitalRead(GREEN_BUTTON) == LOW && previous_contact == false)
    {
        green_button_ms = millis();
        previous_contact = true;
    }
    else if (digitalRead(GREEN_BUTTON) == HIGH && previous_contact == true)
    {
        if (millis() - green_button_ms < 1000)
        {
            Serial.println("GREEN BUTTON");
            // change gear to be send
            uint8_t actual = GEAR::getDesiredGear();
            if (actual == 128)
            {
                actual = 0;
            }
            else if (actual == 255)
            {
                actual = 128;
            }
            else if (actual == 6)
            {
                actual = 255;
            }
            else
            {
                actual++;
            }
            GEAR::setDesiredGear(actual);
        }
        else
        {
            // green_button.longPress();
        }
        previous_contact = false;
    }
    if (digitalRead(RED_BUTTON) == LOW && previous_fss == false)
    {
        red_button_ms = millis();
        previous_fss = true;
    }
    else if (digitalRead(RED_BUTTON) == HIGH && previous_fss == true)
    {
        if (millis() - red_button_ms < 1000)
        {
            Serial.println("RED BUTTON");
            if (CURRENT_SCREEN == 0)
            {

                OBD2::readDTC();
                display.setDebugScreen();
                CURRENT_SCREEN = 1;
            }
            else if (CURRENT_SCREEN == 1)
            {
                display.setSensorScreen();
                CURRENT_SCREEN = 2;
            }
            else
            {
                display.setMainScreen();
                CURRENT_SCREEN = 0;
            }
        }
        else
        {
            OBD2::clearDTC();
            display.setMainScreen();
        }
        previous_fss = false;
    }

    // execute each 100ms
    if (millis() - elapsed_100ms > 100)
    {

        // emulateDash
        if (GEAR::getDesiredGear() != 128)
        {
            OBD2::emulateDash(GEAR::getDesiredGear());
        }
        else
        {
            OBD2::emulateDash(GEAR::getGear());
        }

        // updateScreen
        display.sendTimeEngineOn(time_engine_on);
        // print data to sd and update screen
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