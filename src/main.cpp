#include <Arduino.h>

#include "lib/CAN/OBD2.h"
#include "lib/CAN/emulateDash.h"

#include "lib/persistence/persistance.h"
#include "lib/SD/SDstore.h"

#include "lib/SteeringWheel/SteeringWheel.h"
#include "lib/Radio/Radio.h"

#include "lib/sensors/gear.h"
#include "lib/sensors/buttons.h"



#include "settings.h"

OBD2sensordata OBD2db = {0};
Packet RadioPacket = {0};


void setup() {
    // init serial
    #ifdef DEBUG
    Serial.begin(115200); 
    #endif


    initScreen(ScreenUART);
    initRadio(RadioUART);

    initOBD2(OBD2db);
    initSD();

    initGear();
    pinMode(OIL_PRESSURE_PIN,INPUT);

    rpmled(0);
    OBD2db.engine_rpmA=0;
    OBD2db.engine_rpmB=0;



    pinMode(DEBUG_LED, OUTPUT);
}


uint32_t elapsed_minute = 0;
uint32_t elapsed_second = 0;
uint32_t elapsed_100ms = 0;

boolean previous_contact = false;
boolean previous_fss = false;

void loop() {
    // execute always


    OBD2events();

    // shutdown screen if contact is off
    if (isContact()){
        if (!previous_contact){
            setMainScreen();
            previous_contact = true;
        }
    } else{
        if (previous_contact){
            setSplashScreen();
            previous_contact = false;
        }
    }
    // updateScreen
    sendOBDdata(OBD2db);
    sendGear(getGear());

    sendOil(digitalRead(OIL_PRESSURE_PIN));


    //update rpm LEDS
    rpmledInverse(OBD2RPM(OBD2db)/1000);

    // check buttons
    checkbuttons();



    // execute each 100ms
    if (millis() - elapsed_100ms > 100){
        // emulateDash
        emulateDash(getGear());
        // print data to sd
        String to_save = "";
        to_save += millis();
        to_save += ",";
        to_save += OBD2toCSV(OBD2db);
        // add gear and oil to log
        to_save += ",";
        to_save += String(getGear());
        to_save += ",";
        to_save += String(digitalRead(OIL_PRESSURE_PIN));
        saveLine(to_save);
        elapsed_100ms = millis();
    }

    // execute each second
    if (millis() - elapsed_second > 1000){
        // update radio packet
        //RadioPacket.rpm = OBD2RPM(OBD2db);

        // send data over radio
        //sendPacket(RadioPacket);

        //printOBD2ALL(OBD2db);


        elapsed_second = millis();
    }

    // execute each minute
    if (millis() - elapsed_minute > 60* 1000){

        // increase time alive counter
        increaseTimeCounter(EEPROM_time_base_address);
        // increase engine on time

        if (OBD2db.Fuel_system_status != 0){
            if (previous_fss){
                increaseTimeCounter(EEPROM_fss_base_address);
            }
            previous_fss = true;
        } else {
            previous_fss = false;
        }
    
    elapsed_minute = millis();
    }

}