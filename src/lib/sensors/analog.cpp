#include "analog.h"
namespace ANALOG {
    float readAnalogValue(int pin){
        return (analogRead(pin)* (3.3 / 1023.0))*2;
    }

}