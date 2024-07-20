#ifndef LIB_CONTROLLER_SPIMUX_SPIMUX_H_
#define LIB_CONTROLLER_SPIMUX_SPIMUX_H_

#include <Arduino.h>



class SPIMux
{
public:
    void init();
    void select(int pin);


private:
    int pins[3]={10,36,37};
    // {T.Firewall, T.Refrigerante, T.Aceite}
};


#endif // LIB_CONTROLLER_SPIMUX_SPIMUX_H_