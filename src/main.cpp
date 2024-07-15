#include <Arduino.h>
#include "settings.h"

#include "lib/CAN/OBD2.h"

#include "lib/persistence/persistance.h"

#include "lib/Screen/Screen.h"
#include "lib/Controller/Sensors/Sensors.h"
#include "lib/Controller/Data/Data.h"
// #include "lib/Controller/ADC/MAX11610.h"

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

// ADC object
// MAX11610 adc;

GYRO bnoGyro;
MAX6675Sensor max6675(SCK_PIN, CS_PIN, SO_PIN);

/**----------------------
 *    Normal sensors
 *------------------------**/
Sensor FuelPressure("Presion gasolina", MAPPING, FUEL_PRESSURE_PIN, FUEL_PRESSURE_MIN, FUEL_PRESSURE_MAX, FUEL_PRESSURE_MIN_BAR, FUEL_PRESSURE_MAX_BAR, "bar", false, true, "fuel_p", true);
Sensor OilPressure("Presion aceite", MAPPING, OIL_PRESSURE_PIN, OIL_PRESSURE_MIN, OIL_PRESSURE_MAX, OIL_PRESSURE_MIN_BAR, OIL_PRESSURE_MAX_BAR, "bar", false, false, "oil_p", true);

Sensor SuspensionFrontRight("Suspension delantera derecha", SUSPENSION, SUSPENSION_FRONT_RIGHT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, false, "susp_f_r", true);
Sensor SuspensionFrontLeft("Suspension delantera izquierda", SUSPENSION, SUSPENSION_FRONT_LEFT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, false, "susp_f_l", true);
Sensor SuspensionRearRight("Suspension trasera derecha", SUSPENSION, SUSPENSION_REAR_RIGHT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, false, "susp_r_r", true);
Sensor SuspensionRearLeft("Suspension trasera izquierda", SUSPENSION, SUSPENSION_REAR_LEFT_PIN, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, false, "sus_r_l", true);

// Sensor Firewall("Firewall", TEMPERATURE, max6675.readTemperature(), "ºC", "firewall", true);
/**----------------------
 *    ENCAPSULATED GYRO SENSOR FUNCTIONS
------------------------*/
float getax() { return bnoGyro.getAccelX(); }
float getay() { return bnoGyro.getAccelY(); }
float getaz() { return bnoGyro.getAccelZ(); }
float getYaw() { return bnoGyro.getYaw(); }
float getPitch() { return bnoGyro.getPitch(); }
float getRoll() { return bnoGyro.getRoll(); }
// float getGyroX() { return bnoGyro.getGyroX(); }
// float getGyroY() { return bnoGyro.getGyroY(); }
// float getGyroZ() { return bnoGyro.getGyroZ(); }

Sensor BNOAccelX("Gyro AccelX", VALUE, getax, "m/s2", true, true, "accel_x", true);
Sensor BNOAccelY("Gyro AccelY", VALUE, getay, "m/s2", true, true, "accel_y", true);
Sensor BNOAccelZ("Gyro AccelZ", VALUE, getaz, "m/s2", true, true, "accel_z", true);
Sensor BNOYaw("Gyro Yaw", VALUE, getYaw, "º", true, true, "gyro_yaw", true);
Sensor BNOPitch("Gyro Pitch", VALUE, getPitch, "º", true, true, "gyro_pitch", true);
Sensor BNORoll("Gyro Roll", VALUE, getRoll, "º", true, true, "gyro_roll", true);
// Sensor BNOGyroX("Gyro X", VALUE, getGyroX, "rad/s", true, true, "gyro_angle_x", true);
// Sensor BNOGyroY("Gyro Y", VALUE, getGyroY, "rad/s", true, true, "gyro_angle_y", true);
// Sensor BNOGyroZ("Gyro Z", VALUE, getGyroZ, "rad/s", true, true, "gyro_angle_z", true);

/**----------------------
 *    ADC Sensors
 *------------------------**/
// Sensor ADC1("Sensor 1", VALUE, adc.readADC(0), "V", false, false, "adc1", true);

// name, type, pin, min, max, min_ext, max_ext, typo_value, key, allow_to_send
// Sensor ADC2("Sensor 2 mapping value", MAPPING, adc.readADC(1), 1, 5, 0, 100, "V", false, false, "adc2", true);

/**----------------------
 *    Gear sensors
 *------------------------**/
Sensor Gear("Gear", VALUE, GEAR::getGear, "gear", false, true, "gear", true);

/**----------------------
 *    ODB Sensors
 *------------------------**/

Sensor ODBRpm("RPM", VALUE, OBD2::getRPM, "RPM", false, true, "rpm", true);
Sensor ODBCoolantTemp("Temperatura refrigerante", VALUE, OBD2::getEngineCoolantTemp, "ºC", false, true, "watertemp", true);
Sensor ODBAirTemp("Temperatura aire", VALUE, OBD2::getAirIntakeTemp, "ºC", false, true, "airtemp", true);
Sensor ODBThrottle("TPS abs", VALUE, OBD2::getObdTPS, "%", true, true, "throttle", true);
Sensor ODBThrottleRel("TPS rel", VALUE, OBD2::getRelativeThrottlePosition, "%", true, true, "throttlerel", true);

Sensor ODBAbsPressure("Presion absoluta", VALUE, OBD2::getBarometricPressure, "kPa", false, false, "abspressure", true);
Sensor ODBIntakePressure("Presion admision", VALUE, OBD2::getIntakeManifoldAbsPressure, "kPa", false, true, "presIntake", true);
Sensor ODBDTCCount("DTC", VALUE, OBD2::getDTC, "DTC", false, false, "dtc", true);

Sensor ODBVoltage("Voltaje", VALUE, OBD2::getControlModuleVoltage, "V", true, true, "voltage", true);
Sensor ODBEngineLoad("Carga motor", VALUE, OBD2::getEngineLoad, "%", true, false, "engineload", true);
// sendFuelSystemStatus(OBD2db.fuel_system_status);

Sensor ODBTrim("Trim", VALUE, OBD2::getLongTermFuelTrim, "%", true, false, "FT", true);
Sensor ODB02Trim("Trim O2", VALUE, OBD2::getOxygenSensorFuelTrim, "%", true, false, "O2trim", true);
Sensor ODB02Volt("Voltaje O2", VALUE, OBD2::getOxygenSensorVoltage, "V", true, false, "O2v", true);

Sensor ODBTimingAdvance("Avance", VALUE, OBD2::getTimingAdvance, "º", false, false, "Tadv", true);
Sensor ODBSpeed("Velocidad", VALUE, OBD2::getSpeed, "km/h", false, false, "speed", true);

// sendDesiredGear(GEAR::getDesiredGear());

// Controlador de datos
Data dataManager(100, TelemetryUART, &display);

float getMillis(){return (float) dataManager.getMillis();}
Sensor Timestamp("Timestamp", VALUE, getMillis, "ms", false, true, "timestamp", true);

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

IntervalTimer EmulateDashTimer;

void setup()
{
    /**----------------------------------------------
     * !                  SI NO VA EL CODIGO
     *   - Estan todas las variables inicializadas?
     *   - Estas haciendo los inits de wire, serial, i2c... en el setup?
     *   - Estas haciendo los inits de los sensores en el setup?
     *   - Hay algun pin digital o analogico iniciandose fuera del setup?
     *---------------------------------------------**/

    // init serial
    Serial.begin(115200);
    Serial.println("Starting...");

    // EmulateDashTimer.priority(255);
    // EmulateDashTimer.begin((int)OBD2::emulateDash, 100000);

    Serial.print("Initalizing data manager...");
    dataManager.init();
    Serial.println("OK!");

    // Serial.print("Initalizing adc...");
    // adc.init(0x34);
    // Serial.println("NOPE!");

    /**--------------------------------------------
     *               Init sensors
     *---------------------------------------------**/
    FuelPressure.init();
    OilPressure.init();
    SuspensionFrontRight.init();
    SuspensionFrontLeft.init();
    SuspensionRearRight.init();
    SuspensionRearLeft.init();
    bnoGyro.begin();

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
    dataManager.addSensor(&Gear);

    /**----------------------
     *    GYRO sensors (Now we use BNO08x family model)
    ------------------------*/
    dataManager.addSensor(&BNOAccelX);
    dataManager.addSensor(&BNOAccelY);
    dataManager.addSensor(&BNOAccelZ);
    dataManager.addSensor(&BNOYaw);
    dataManager.addSensor(&BNOPitch);
    dataManager.addSensor(&BNORoll);
    // dataManager.addSensor(&BNOGyroX);
    // dataManager.addSensor(&BNOGyroY);
    // dataManager.addSensor(&BNOGyroZ);

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

    dataManager.addSensor(&Timestamp);

    dataManager.saveHeaders();

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
     *               Init buttons
     *---------------------------------------------**/
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
    pinMode(RED_BUTTON, INPUT_PULLUP);

    display.setSensorScreen();
}

void loop()
{

    // while (true)
    // {
    //     Serial.println("A");
    //     delay(100);
    // }

    OBD2::OBD2events();
    bnoGyro.loop();
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