#include "buttons.h"

uint32_t last_time_green_pressed = 0;
uint32_t last_time_red_pressed = 0;
bool previous_red = false;

void checkbuttons(){
    // if button pressed
    if (digitalRead(GREEN_BUTTON) == 0 && isContact()){
        if (millis() - last_time_green_pressed < 1000){
            return;
        }
        clearDTC();
        setMainScreen();
        previous_red = false;
        last_time_green_pressed = millis();
    }

        if (digitalRead(RED_BUTTON) == 0 && isContact()){
        if (millis() - last_time_red_pressed < 1000){
            return;
        }
        if (!previous_red){

            readDTC();
            //digitalWrite(DEBUG_LED, HIGH);
            setDebugScreen();
            previous_red = true;
        } else {
            //digitalWrite(DEBUG_LED, LOW);
                setMainScreen();
            previous_red = false;
        }

        last_time_red_pressed = millis();
    }


}
