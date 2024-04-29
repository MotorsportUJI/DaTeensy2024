#include "SparkFun_BNO08x_Arduino_Library.h"
#include <math.h>

#ifndef GYRO_H
#define GYRO_H

/**-------------------------
 * FOR DEBUGGING PURPOSES :)
 * -------------------------
 */

#define GYRO_H_DEBUG

// For the most reliable interaction with the SHTP bus, we need
// to use hardware reset control, and to monitor the H_INT pin.
// The H_INT pin will go low when its okay to talk on the SHTP bus.
// Note, these can be other GPIO if you like.
// Define as -1 to disable these features.
// #define BNO08X_INT A4
#define BNO08X_INT 23
// #define BNO08X_RST A5
#define BNO08X_RST 22

#define BNO08X_ADDR 0x4B // SparkFun BNO08x Breakout (Qwiic) defaults to 0x4B (we use 0x68)
// #define BNO08X_ADDR 0x4A // Alternate address if ADR jumper is closed

struct GYROData
{
    float yaw;
    float pitch;
    float roll;
    float accelX;
    float accelY;
    float accelZ;
    float gyroX;
    float gyroY;
    float gyroZ;
};

class GYRO
{
public:
    GYRO();

    void begin();
    void loop();
    void calibrate();

    // Acererometer
    float getAccelX();
    float getAccelY();
    float getAccelZ();

    // GYRO
    float getGyroX();
    float getGyroY();
    float getGyroZ();

    // Euler
    float getYaw();
    float getPitch();
    float getRoll();

    // debug
    void printDataDebug();

private:
    GYROData data;
    uint32_t lastUpdate = 0;
    void setReports(void);
};

#endif // GYRO_H
