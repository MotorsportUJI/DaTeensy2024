#ifndef GYRO_H
#define GYRO_H

#include "MPU9250.h"
#include <math.h>

struct GYROData
{
    float yaw;
    float pitch;
    float roll;
    float accelX;
    float accelY;
    float accelZ;
    float magX;
    float magY;
    float magZ;
};

class GYRO
{
public:
    GYRO();

    void begin();
    void loop();
    float getYaw();
    float getPitch();
    float getRoll();
    float getAccelX();
    float getAccelY();
    float getAccelZ();
    float getMagX();
    float getMagY();
    float getMagZ();

private:
    GYROData data;
    uint32_t lastUpdate = 0;
};

#endif // GYRO_H
