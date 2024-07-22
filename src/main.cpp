#include <Arduino.h>
#include "settings.h"

#include "lib/persistence/persistance.h"

#include "lib/Screen/Screen.h"
#include "lib/Controller/Data/Data.h"

#include "lib/CAN/OBD2.h"
#include "lib/Controller/Sensors/Sensors.h"
#include "lib/Controller/ADC/MAX11610.h"
#include "lib/sensors/gear.h"
// Termopar snesor
#include "lib/sensors/Termopar.h"
// Gyro sensor
#include "lib/sensors/GYRO.h"
// I2C Mux
#include "lib/Controller/I2CMux/TCA9548A.h"
// ADC
#include "lib/Controller/ADC/MAX11610.h"

// MUX
#include "lib/Controller/MUX/CD74HC4067SM96.h"

//SPI MUX
#include "lib/Controller/SPIMux/SPIMux.h"

// Leds
#include "lib/Controller/LED/LED.h"

// Buttons
#include "lib/Controller/Button/BUTTON.h"

// Velocidad
#include "lib/sensors/Velocidad.h"

/**----------------------
 *    OBD
 *------------------------**/
OBD2::OBD2sensordata OBD2db = {0};


/**----------------------
 *    MUX TCA (I2C)
 *------------------------**/
TCA9548A tca;


/**----------------------
 *    SPI Mux
 *------------------------**/

SPIMux spiMux;

/**----------------------
 *    MUX  (Normal)
 *------------------------**/
CD74HC4067SM96 mux;

int readPin0() {return mux.read0();}
int readPin1() {return mux.read1();}
int readPin2() {return mux.read2();}
int readPin3() {return mux.read3();}
int readPin4() {return mux.read4();}
int readPin5() {return mux.read5();}
int readPin6() {return mux.read6();}
int readPin7() {return mux.read7();}

/**----------------------
 *    Gyro
 *------------------------**/

GYRO bnoGyro(&tca);

float getax() { return bnoGyro.getAccelX(); }
float getay() { return bnoGyro.getAccelY(); }
float getaz() { return bnoGyro.getAccelZ(); }
float getYaw() { return bnoGyro.getYaw(); }
float getPitch() { return bnoGyro.getPitch(); }
float getRoll() { return bnoGyro.getRoll(); }
float getGyroX() { return bnoGyro.getGyroX(); }
float getGyroY() { return bnoGyro.getGyroY(); }
float getGyroZ() { return bnoGyro.getGyroZ(); }


Sensor BNOAccelX("Gyro AccelX", VALUE, getax, "m/s2", true, true, "accel_x", true);
Sensor BNOAccelY("Gyro AccelY", VALUE, getay, "m/s2", true, true, "accel_y", true);
Sensor BNOAccelZ("Gyro AccelZ", VALUE, getaz, "m/s2", true, true, "accel_z", true);
Sensor BNOYaw("Gyro Yaw", VALUE, getYaw, "º", true, true, "gyro_yaw", true);
Sensor BNOPitch("Gyro Pitch", VALUE, getPitch, "º", true, true, "gyro_pitch", true);
Sensor BNORoll("Gyro Roll", VALUE, getRoll, "º", true, true, "gyro_roll", true);
Sensor BNOGyroX("Gyro X", VALUE, getGyroX, "rad/s", true, true, "gyro_angle_x", true);
Sensor BNOGyroY("Gyro Y", VALUE, getGyroY, "rad/s", true, true, "gyro_angle_y", true);
Sensor BNOGyroZ("Gyro Z", VALUE, getGyroZ, "rad/s", true, true, "gyro_angle_z", true);




/**----------------------
 *    Termopar
 *------------------------**/
Termopar TermoparFirewall(SCK_PIN, FIREWALL_CS_PIN, SO_PIN, &spiMux, 0);
Termopar TermoparRefrigerante(SCK_PIN, RADIADOR_CS_PIN, SO_PIN, &spiMux, 1);
Termopar TermoparAceite(SCK_PIN, ACEITE_CS_PIN, SO_PIN, &spiMux, 2);

float getTFirewall(){return TermoparFirewall.readTemperature();}
float getTRefrigerante(){return TermoparRefrigerante.readTemperature();}
float getTAceite(){return TermoparAceite.readTemperature();}

Sensor TFirewall("T. Firewall", TEMPERATURE, getTFirewall, "ºC", false, true, "tempFirewall", true);
Sensor TRefrigerante("T. Radiador", TEMPERATURE, getTRefrigerante, "ºC", false, true, "tempRadiador", true);
Sensor TAceite("T. Aceite", TEMPERATURE, getTAceite, "ºC", false, true, "tempAceite", true);

/**----------------------
 *    ADC 1
 *------------------------**/
MAX11610 adc1(0x33, 2, &tca);

float readADC10(){    return adc1.readADC0();   }
float readADC11(){    return adc1.readADC1();   }
float readADC12(){    return adc1.readADC2();   }
float readADC13(){    return adc1.readADC3();   }
float readADC14(){    return adc1.readADC4();   }
float readADC15(){    return adc1.readADC5();   }
float readADC16(){    return adc1.readADC6();   }
float readADC17(){    return adc1.readADC7();   }
float readADC18(){    return adc1.readADC8();   }
float readADC19(){    return adc1.readADC9();   }
float readADC110(){   return adc1.readADC10();  }

Sensor TPS2("TPS2", VALUE, readADC10, "V", false, false, "tps2", true);
Sensor PresionCombustible("PresionCombustible", MAPPING, readADC11, FUEL_PRESSURE_MIN, FUEL_PRESSURE_MAX, FUEL_PRESSURE_MIN_BAR, FUEL_PRESSURE_MAX_BAR, "bar", false, true, "fuel_p", true);
Sensor CaudalAire("CaudalAire", VALUE, readADC12, "V", false, false, "airflow", true);
Sensor libre1("libre1", VALUE, readADC13, "V", false, false, "libre1", true);
Sensor libre2("libre2", VALUE, readADC14, "V", false, false, "libre2", true);
Sensor libre3("libre3", VALUE, readADC15, "V", false, false, "libre3", true);
Sensor SuspensionFrontRight("Suspension delantera derecha", SUSPENSION, readADC17, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, false, "susp_f_r", true);
Sensor SuspensionFrontLeft("Suspension delantera izquierda", SUSPENSION, readADC18, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, false, "susp_f_l", true);
Sensor SuspensionRearRight("Suspension trasera derecha", SUSPENSION, readADC19, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, false, "susp_r_r", true);
Sensor SuspensionRearLeft("Suspension trasera izquierda", SUSPENSION, readADC110, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, false, "sus_r_l", true);


/**----------------------
 *    ADC 2
 *------------------------**/
MAX11610 adc2(0x34, 3, &tca);

float readADC20 (){ return adc2.readADC0(); }
float readADC21 (){ return adc2.readADC1(); }
float readADC22 (){ return adc2.readADC2(); }
float readADC23 (){ return adc2.readADC3(); }
float readADC24 (){ return adc2.readADC4(); }


Sensor PAireAdmision2FPB("Presion de aire de admision", MAPPING, readADC20, MIN_ADMISSION, MAX_ADMISSION, MIN_ADMISSION_BAR, MAX_ADMISSION_BAR, "bar", false, false, "adm_p", true);
Sensor PCalderinFPB("Presion del calderin", MAPPING, readADC21, MIN_CALDERIN, MAX_CALDERIN, MIN_CALDERIN_BAR, MAX_CALDERIN_BAR, "bar", false, false, "calder_p", true);
Sensor OilPressure("Presion aceite", MAPPING, readADC22, OIL_PRESSURE_MIN, OIL_PRESSURE_MAX, OIL_PRESSURE_MIN_BAR, OIL_PRESSURE_MAX_BAR, "bar", false, false, "oil_p", true);


/**----------------------
 *    Gear 
 *------------------------**/
Sensor Gear("Gear", VALUE, GEAR::getGear, "gear", false, true, "gear", true);
Sensor PresionFreno("PresionFreno", VALUE, readADC16, "V", false, false, "brake_p", true);


/**----------------------
 *    Freno
 *------------------------**/

/**----------------------
 *    Hall (Velocidad)
 *------------------------**/
VELOCIDAD velocidad;

float getAvgSpeed() { return velocidad.getSpeed() ;}
Sensor AvgSpeed("Velocidad media", VALUE, getAvgSpeed, "Km/h", false, true, "speed", true);

/**----------------------
 *    ODB Sensors
 *------------------------**/

Sensor ODBRpm("RPM", VALUE, OBD2::getRPM, "RPM", false, true, "rpm", true);
Sensor ODBCoolantTemp("Temperatura refrigerante", VALUE, OBD2::getEngineCoolantTemp, "ºC", false, true, "watertemp", true);
Sensor ODBAirTemp("Temperatura aire", VALUE, OBD2::getAirIntakeTemp, "ºC", false, true, "airtemp", true);
Sensor ODBThrottle("TPS abs", VALUE, OBD2::getObdTPS, "%", true, true, "throttle", true);
Sensor ODBThrottleRel("TPS rel", VALUE, OBD2::getRelativeThrottlePosition, "%", true, true, "throttlerel", true);

Sensor ODBAbsPressure("Presion absoluta", VALUE, OBD2::getBarometricPressure, "kPa", false, false, "abspressure", true);
Sensor ODBIntakePressure("Presion admFion", VALUE, OBD2::getIntakeManifoldAbsPressure, "kPa", false, true, "presIntake", true);
Sensor ODBDTCCount("DTC", VALUE, OBD2::getDTC, "DTC", false, false, "dtc", true);

Sensor ODBVoltage("Voltaje", VALUE, OBD2::getControlModuleVoltage, "V", true, true, "voltage", true);
Sensor ODBEngineLoad("Carga motor", VALUE, OBD2::getEngineLoad, "%", true, false, "engineload", true);
// sendFuelSystemStatus(OBD2db.fuel_system_status);

Sensor ODBTrim("Trim", VALUE, OBD2::getLongTermFuelTrim, "%", true, false, "FT", true);
Sensor ODB02Trim("Trim O2", VALUE, OBD2::getOxygenSensorFuelTrim, "%", true, false, "O2trim", true);
Sensor ODB02Volt("Voltaje O2", VALUE, OBD2::getOxygenSensorVoltage, "V", true, false, "O2v", true);

Sensor ODBTimingAdvance("Avance", VALUE, OBD2::getTimingAdvance, "º", false, false, "Tadv", true);

// TODO Donde van
/**---------------------- 
 *    Sensor direccion
 *------------------------**/
Sensor SteeringAngle("AnguloDireccion", VALUE, OBD2::getSpeed, "km/h", false, true, "speed", true);



// LED
LED led;
int ledEffect = 0;
int valueReadIndex = 0;
int (*ledValue)();

/**----------------------
 *    Display
 *------------------------**/
Display display(ScreenUART);
int CURRENT_SCREEN = 0;

/**----------------------
 *    Botones
 *------------------------**/
BUTTON BotonCambioPantalla(B1, []() {
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
}, 1000);

BUTTON CambiarEfectoLed(B2, []() {
    if(ledEffect == 0){
        led.rainbow();
        ledEffect = 1;
    }else if(ledEffect == 1){
        led.rainbowWithGlitter();
        ledEffect = 2;
    // }else if(ledEffect == 2){
    //     led.confetti();
    //     ledEffect = 3;
    }else if(ledEffect == 2){
        led.sinelon();
        ledEffect = 3;
    }else if(ledEffect == 3){
        led.set_line((uint8_t *) 0xFF8001, (uint8_t *)0x21BBFD, ledValue);
        ledEffect = 4;
    }else{
        led.set_line((uint8_t *)0x076B00, (uint8_t *)0xC60404, ledValue);
        ledEffect = 0;
    }

}, 1000);

int readRPMLed(){return map(OBD2::getRPM(), 0, 12000, 0, NUM_LEDS);}
int readTPSLed(){return map(OBD2::getObdTPS(), 0, 100, 0, NUM_LEDS);}


BUTTON CambiarEntradaLed(B3, []() {
    if(valueReadIndex == 0){
        
        ledValue = &readRPMLed;
        valueReadIndex = 1;
    }
}, 1000);


BUTTON Unused(B4, []() {
    // print("Unused button");
}, 1000);



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
     *   - Si no va es por culpa de gyro. qiutarlo del begin y del loop
     *---------------------------------------------**/

    // init serial
    Serial.begin(115200);
    Serial.println("Starting...");

    // EmulateDashTimer.priority(255);
    // EmulateDashTimer.begin((int)OBD2::emulateDash, 100000);

    Serial.print("Initalizing data manager...");
    dataManager.init();
    Serial.println("OK!");


    /**----------------------
     *    PIN DEL RELÉ DE LA LUZ DE FRENO
     *------------------------**/

    pinMode(RELAY_PIN, OUTPUT);

    /**----------------------
     *    VELOCIDAD (HALL)
     *------------------------**/

    velocidad.loop();

    // Serial.print("Initalizing adc...");
    // adc.init(0x34);
    // Serial.println("NOPE!");

    /**--------------------------------------------
     *               Init sensors
     *---------------------------------------------**/
    bnoGyro.begin();
    
    /**----------------------
     *    Hall
     *------------------------**/
    velocidad.addHall(6);
    velocidad.addHall(9);

    /**--------------------------------------------
     *               Initi data logger
     *---------------------------------------------**/

    // Add sensors to data manager
    dataManager.addSensor(&PresionCombustible);
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
    dataManager.addSensor(&ODBAbsPressure);
    dataManager.addSensor(&ODBDTCCount);

    dataManager.addSensor(&Timestamp);

    dataManager.saveHeaders();

    /**--------------------------------------------
     *               SPI Sensors
     *---------------------------------------------**/

    dataManager.addSensor(&TFirewall);
    dataManager.addSensor(&TRefrigerante);
    dataManager.addSensor(&TAceite);
    

    /**--------------------------------------------
     *               Init OBD2
     *---------------------------------------------**/
    initOBD2(OBD2db);

    /**--------------------------------------------
     *               Init GEAR
     *---------------------------------------------**/
    GEAR::initGear(&mux);

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
    BotonCambioPantalla.init();
    CambiarEfectoLed.init();
    CambiarEntradaLed.init();
    Unused.init();

    /**----------------------
     *    LED
     *------------------------**/
    led.init();
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

    /**----------------------
     *    GYRO
     *------------------------**/
    bnoGyro.loop(); 

    /**----------------------
     *    Velocidad
     *------------------------**/
    velocidad.loop();

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
     *    Button update
     *------------------------**/
    BotonCambioPantalla.update();
    CambiarEfectoLed.update();
    CambiarEntradaLed.update();
    Unused.update();

    /**----------------------
     *    LED
     *------------------------**/
    led.loop();

    /**----------------------
     *    FRENO (Si se presiona el freno, activar relé conectado al pin 2)
     *------------------------**/

    if (PresionFreno.read() > 0) {
        digitalWrite(RELAY_PIN, HIGH);
    } else {
        digitalWrite(RELAY_PIN, LOW);
    }

    /**--------------------------------------------
     *               NO TOCAR
     *---------------------------------------------**/
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

        /**--------------------------------------------
         *               EL LOOP
         *---------------------------------------------**/
        display.sendTimeEngineOn(time_engine_on);
        // print data to sd and update screen
        // dataManager.loop();
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