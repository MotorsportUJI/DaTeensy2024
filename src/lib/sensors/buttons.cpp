#include "buttons.h"

uint32_t last_time_green_pressed = 0;
uint32_t last_time_red_pressed = 0;
void checkbuttons(){
    // if button pressed
    if (digitalRead(GREEN_BUTTON) == 0){
        if (millis() - last_time_green_pressed < 1000){
            return;
        }
        //Serial.println("pressed");
            // clear dtc
        //digitalToggle(DEBUG_LED);

        last_time_green_pressed = millis();
    }

        if (digitalRead(RED_BUTTON) == 0){
        if (millis() - last_time_red_pressed < 1000){
            return;
        }
        //Serial.println("pressed");
            // clear dtc
        //digitalToggle(DEBUG_LED);
        // change screen and lookup dtc

        last_time_red_pressed = millis();
    }


}
