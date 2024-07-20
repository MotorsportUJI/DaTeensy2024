#ifndef LIB_CONTROLLER_I2CMUX_TCA9548A_H_
#define LIB_CONTROLLER_I2CMUX_TCA9548A_H_


// #define TCA_PORT_NUMBER 8
#include <Wire.h>
#define TCAADDR 0x70

/**
 * Controller for the TCA9548A I2C multiplexer
 * This requires to enable Wire and serial prior to the use of the class
 */

class TCA9548A {
    // Función para leer del multiplexor
    public:
        void pcaselect(uint8_t i);
        uint8_t getAddress();
    private:
        uint8_t pin =-1;
};

#endif // LIB_CONTROLLER_I2CMUX_TCA9548A_H_