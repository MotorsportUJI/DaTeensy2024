#include "gear.h"

namespace GEAR
{
    CD74HC4067SM96* _muxGear = nullptr;  // Define the variable

    void initGear(CD74HC4067SM96 *mux)
    {
        _muxGear = mux;
    }

    float getGear()
    {
        if (!_muxGear->read0())
        {
            return 0;
        }
        else if (!_muxGear->read1())
        {
            return 1;
        }
        else if (!_muxGear->read2())
        {
            return 2;
        }
        else if (!_muxGear->read3())
        {
            return 3;
        }
        else if (!_muxGear->read4())
        {
            return 4;
        }
        else if (!_muxGear->read5())
        {
            return 5;
        }
        else if (!_muxGear->read6())
        {
            return 6;
        }

        for (int i = 0; i < 7; i++)
        {
            if (!_muxGear->readPin(i))
            {
                return 6 - i;
            }
        }
        return 88;
    }

    uint8_t desired_gear = 128;
    uint8_t getDesiredGear()
    {
        return desired_gear;
    }

    void setDesiredGear(uint8_t gear)
    {
        desired_gear = gear;
    }
}
