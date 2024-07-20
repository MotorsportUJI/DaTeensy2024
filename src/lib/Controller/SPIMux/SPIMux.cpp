#include "SPIMux.h"


void SPIMux::init(){
    for (int i = 0; i < 3; i++){
        pinMode(pins[i], OUTPUT);
    }
    select(0);
}
void SPIMux::select(int pin) {
    for (int i = 0; i < 3; i++){
        digitalWrite(pins[i], LOW);
    }
    digitalWrite(pins[pin], HIGH);
}