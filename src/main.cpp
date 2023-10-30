#include <Arduino.h>
#include "settings.h"

#include "lib/CAN/OBD2.h"

#include "lib/persistence/persistance.h"
#include "lib/Controller/SD/SDstore.h"

#include "lib/SteeringWheel/SteeringWheel.h"
#include "lib/Controller/Telemetry/Telemetry.h"
#include "lib/Controller/Sensors/Sensors.h"
#include "lib/Controller/Data/Data.h"
#include "lib/Controller/ADC/MAX11610.h"

#include "lib/sensors/gear.h"

// Gyro sensor
#include "lib/sensors/GYRO.h"

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

// ADC object
MAX11610 adc;

GYRO axis6;
// MAX6675Sensor max6675(SCK_PIN, CS_PIN, SO_PIN);

/**----------------------
 *    Normal sensors
 *------------------------**/
Sensor FuelPressure("Presion gasolina", PRESSURE, FUEL_PRESSURE_PIN, FUEL_PRESSURE_MIN, FUEL_PRESSURE_MAX, FUEL_PRESSURE_MIN_BAR, FUEL_PRESSURE_MAX_BAR, "bar", false, "fuel_p", true);
Sensor OilPressure("Presion aceite", PRESSURE, OIL_PRESSURE_PIN, OIL_PRESSURE_MIN, OIL_PRESSURE_MAX, OIL_PRESSURE_MIN_BAR, OIL_PRESSURE_MAX_BAR, "bar", false, "oil_p", true);

Sensor SuspensionFrontRight("Suspension delantera derecha", SUSPENSION, SUSPENSION_FRONT_RIGHT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, "susp_f_r", true);
Sensor SuspensionFrontLeft("Suspension delantera izquierda", SUSPENSION, SUSPENSION_FRONT_LEFT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, "susp_f_l", true);
Sensor SuspensionRearRight("Suspension trasera derecha", SUSPENSION, SUSPENSION_REAR_RIGHT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, "susp_r_r", true);
Sensor SuspensionRearLeft("Suspension trasera izquierda", SUSPENSION, SUSPENSION_REAR_LEFT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, "sus_r_l", true);

// Sensor Firewall("Firewall", TEMPERATURE, max6675.readTemperature(), "ºC", "firewall", true);

// float g1()
// {
//     return axis6.getPitch();
// }
// float g2()
// {
//     return axis6.getYaw();
// }

// Sensor GyroAngle("Gyro Angulo", VALUE, g1, "º", false, "gyro_angle", true);
// Sensor GyroSpeed("Gyro Velocidad", VALUE, g2, "º/s", false, "gyro_speed", true);

/**----------------------
 *    ADC Sensors
 *------------------------**/
Sensor ADC1("Sensor 1", VALUE, adc.readADC(0), "V", false, "adc1", true);

// name, type, pin, min, max, min_ext, max_ext, typo_value, key, allow_to_send
Sensor ADC2("Sensor 2 mapping value", MAPPING, adc.readADC(1), 1, 5, 0, 100, "V", false, "adc2", true);

/**----------------------
 *    Gear sensors
 *------------------------**/
Sensor Gear("Gear", VALUE, GEAR::getGear, "gear", false, "gear", true);

// odb sensors

Sensor ODBRpm("RPM", VALUE, OBD2::getRPM, "RPM", false, "rpm", true);
Sensor ODBCoolantTemp("Temperatura refrigerante", VALUE, OBD2::getEngineCoolantTemp, "ºC", false, "watertemp", true);
Sensor ODBAirTemp("Temperatura aire", VALUE, OBD2::getAirIntakeTemp, "ºC", false, "airtemp", true);
Sensor ODBThrottle("Acelerador", VALUE, OBD2::getObdTPS, "%", true, "throttle", true);
Sensor ODBThrottleRel("Acelerador relativo", VALUE, OBD2::getRelativeThrottlePosition, "%", true, "throttlerel", true);

Sensor ODBAbsPressure("Presion absoluta", VALUE, OBD2::getBarometricPressure, "kPa", false, "abspressure", true);
Sensor ODBIntakePressure("Presion admision", VALUE, OBD2::getIntakeManifoldAbsPressure, "kPa", false, "presIntake", true);
Sensor ODBDTCCount("DTC", VALUE, OBD2::getDTC, "DTC", false, "dtc", true);

Sensor ODBVoltage("Voltaje", VALUE, OBD2::getControlModuleVoltage, "V", true, "voltage", true);
Sensor ODBEngineLoad("Carga motor", VALUE, OBD2::getEngineLoad, "%", true, "engineload", true);
// sendFuelSystemStatus(OBD2db.fuel_system_status);

Sensor ODBTrim("Trim", VALUE, OBD2::getLongTermFuelTrim, "%", true, "FT", true);
Sensor ODB02Trim("Trim O2", VALUE, OBD2::getOxygenSensorFuelTrim, "%", true, "O2trim", true);
Sensor ODB02Volt("Voltaje O2", VALUE, OBD2::getOxygenSensorVoltage, "V", true, "O2v", true);

Sensor ODBTimingAdvance("Avance", VALUE, OBD2::getTimingAdvance, "º", false, "Tadv", true);
Sensor ODBSpeed("Velocidad", VALUE, OBD2::getSpeed, "km/h", false, "speed", true);

//     sendDesiredGear(GEAR::getDesiredGear());

// Controlador de datos
Data dataManager(100, telemetry, sdstore, &display);

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
    Serial.begin(115200);

    Serial.println("Starting...");

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
    axis6.begin();

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
    // dataManager.addSensor(&Firewall);
    // dataManager.addSensor(&GyroAngle);
    // dataManager.addSensor(&GyroSpeed);
    dataManager.addSensor(&Gear);

    // OBD2 sensors data manager
    dataManager.addSensor(&ODBRpm);
    dataManager.addSensor(&ODBCoolantTemp);
    dataManager.addSensor(&ODBAirTemp); // no need
    dataManager.addSensor(&ODBThrottle);
    dataManager.addSensor(&ODBThrottleRel);
    dataManager.addSensor(&ODBIntakePressure);
    dataManager.addSensor(&ODBTrim);   // no
    dataManager.addSensor(&ODB02Trim); // no
    dataManager.addSensor(&ODB02Volt);
    dataManager.addSensor(&ODBVoltage);
    dataManager.addSensor(&ODBEngineLoad);
    dataManager.addSensor(&ODBTimingAdvance);
    dataManager.addSensor(&ODBSpeed);
    dataManager.addSensor(&ODBAbsPressure);
    dataManager.addSensor(&ODBDTCCount);

    /**--------------------------------------------
     *               Init OBD2
     *---------------------------------------------**/
    initOBD2(OBD2db);

    /**--------------------------------------------
     *               Init GEAR
     *---------------------------------------------**/
    GEAR::initGear();

    /**--------------------------------------------
     *               Init display
     *---------------------------------------------**/
    display.init();
    display.rpmled(0);
    display.setMainScreen();

    OBD2db.engine_rpmA = 0;
    OBD2db.engine_rpmB = 0;

    pinMode(DEBUG_LED, OUTPUT);
    delay(1000);

    /**--------------------------------------------
     *               Init Gravitational sensor
     *---------------------------------------------**/
    // axis6.begin();

    /**--------------------------------------------
     *               Init buttons
     *---------------------------------------------**/
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
    pinMode(RED_BUTTON, INPUT_PULLUP);

    display.setSensorScreen();
}

void loop()
{

    OBD2::OBD2events();
    axis6.loop();
    // Serial.print(axis6.getYaw());
    // Serial.print(" | ");
    // Serial.print(axis6.getPitch());
    // Serial.print(" | ");
    // Serial.print(axis6.getRoll());
    // Serial.print(" | | |  ");
    // Serial.print(axis6.getAccelX());
    // Serial.print(" | ");
    // Serial.print(axis6.getAccelY());
    // Serial.print(" | ");
    // Serial.println(axis6.getAccelZ());

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
                display.setSplashScreen();
                CURRENT_SCREEN = 1;
            }
            else if (CURRENT_SCREEN == 1)
            {
                display.setSensorScreen();
                CURRENT_SCREEN = 2;
            }
            else if (CURRENT_SCREEN == 2)
            {
                display.setMainScreen();
                CURRENT_SCREEN = 3;
            }
            else if (CURRENT_SCREEN == 3)
            {
                display.setDebugScreen();
                CURRENT_SCREEN = 0;
            }
            Serial.println("Pantalla: " + String(CURRENT_SCREEN));
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