#include "Velocidad.h"
#include <Arduino.h>

// TODO: Ten en cuenta que pued tener 1 o N sensores hall, por lo que deberías tener un array de pines
// y un array de revoluciones

VELOCIDAD::VELOCIDAD(){
    _hallSensors = 0;
}

void VELOCIDAD::addHall(int pin){
    _pin[_hallSensors] = pin;
    _hallSensors++;
}

void VELOCIDAD::init(){ 
    for (int i = 0; i < _hallSensors; i++) {
        pinMode(_pin[i], INPUT);
    }
}

void VELOCIDAD::fromRevsToSpeed(float revs) {
    speed = (PI * 0.2 * revs) / 60;
}


float VELOCIDAD::getSpeed() {  
    int avgRevs = 0;
    for (int i = 0; i < _hallSensors; i++) {
        avgRevs += _revs[i];
    }
    avgRevs /= _hallSensors;

    fromRevsToSpeed(avgRevs);

    return speed;
}


void VELOCIDAD::loop(){
    for (int i = 0; i < _hallSensors; i++) {
        if (digitalRead(_pin[i]) == HIGH){
            _times[i][0] = millis(); // fi 
            _revs[i] = 60*1000/(_times[i][0] - _times[i][1]);
            _times[i][1] = _times[i][0];
        }
    }

}