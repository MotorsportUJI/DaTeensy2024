#include "TCA9548A.h"

/**
 * @brief Selects the channel to read from the multiplexer
 * @param i Channel number
 */
void TCA9548A::pcaselect(uint8_t i) {
    if (pin == i) {return;}
    
    if (i > 7) {
        return;
    }
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << i);
    Wire.endTransmission();
}

uint8_t TCA9548A::getAddress(){
    return TCAADDR;
}