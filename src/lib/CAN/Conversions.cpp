#include "OBD2.h"
#include "map"

namespace OBD2CONVERSIONS
{

    std::map<int, int> points = {
        {200, 225},
        {400, 450},
        {600, 675},
        {800, 900},
        {1000, 1150},
        {2000, 2200},
        {3000, 3250},
        {4000, 4300},
        {5000, 5400},
        {6000, 6500},
        {7000, 7500},
        {8000, 8500},
        {9000, 9500},
        {10000, 10500},
        {11000, 11500},
        {15500, 16000}, // No van a superar estos valores pero para que cuadre bien
        {20000, 20500}};

    uint16_t OBD2RPM(OBD2::OBD2sensordata db)
    {
        uint16_t rpm = (db.engine_rpmA * 256 + db.engine_rpmB) / 4;
        if (rpm < 250)
        {
            return rpm;
        }

        auto upper = points.lower_bound(rpm);
        if (upper == points.begin())
            return upper->second;
        if (upper == points.end())
            return std::prev(upper)->second;
        auto lower = std::prev(upper);
        double t = (double)(rpm - lower->first) / (upper->first - lower->first);
        return (1 - t) * lower->second + t * upper->second;
    }

    float OBD2TMP(uint8_t tmp)
    {
        // coolant Temp
        return float(tmp) - 40.0;
    }

    float OBD2PC(uint8_t tmp)
    {
        return float(tmp) / 2.55;
    }

    float OBD2Trim(uint8_t tmp)
    {
        return float(tmp) / 1.28 - 100;
    }

    float OBD2Volt(OBD2::OBD2sensordata db)
    {
        return (db.control_module_voltage_A * 256 + db.control_module_voltage_B) / 1000.0;
    }

    float OBD2VoltO2(uint8_t v)
    {
        return v / 200;
    }

    float OBD2Advance(uint8_t v)
    {
        return (v / 2) - 64;
    }

}