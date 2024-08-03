#include "CD74HC4067SM96.h"


void CD74HC4067SM96::init(int readPin, int pinS0, int pinS1, int pinS2, int pinS3) {
    _readPin = readPin;
    _mux = new CD74HC4067(pinS0, pinS1, pinS2, pinS3);  // Dynamically allocate the object

    pinMode(_readPin, INPUT);
}

int CD74HC4067SM96::readPin(int pin){
    _mux->channel(pin);
    return digitalRead(_readPin);
}

int CD74HC4067SM96::read0(){
    return readPin(0);
}

int CD74HC4067SM96::read1(){
    return readPin(1);
}

int CD74HC4067SM96::read2(){
    return readPin(2);
}

int CD74HC4067SM96::read3(){
    return readPin(3);
}

int CD74HC4067SM96::read4(){
    return readPin(4);
}

int CD74HC4067SM96::read5(){
    return readPin(5);
}

int CD74HC4067SM96::read6(){
    return readPin(6);
}

int CD74HC4067SM96::read7(){
    return readPin(7);
}