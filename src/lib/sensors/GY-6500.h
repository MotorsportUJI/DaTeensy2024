#ifndef GY6500_SENSOR_H
#define GY6500_SENSOR_H

#include <Wire.h>

class GY6500Sensor
{
public:
    GY6500Sensor(uint8_t deviceAddress, float alpha, float dt);

    void begin();
    void readData();
    float getAngle();
    float getSpeed();

private:
    uint8_t deviceAddress;
    int16_t accelX, accelY, accelZ;
    int16_t gyroX, gyroY, gyroZ;
    float angle, speed;
    float alpha, dt;

    int16_t readWord2C(uint8_t regAddress);
    void calculateAngleSpeed();
};

#endif // GY6500_SENSOR_H
