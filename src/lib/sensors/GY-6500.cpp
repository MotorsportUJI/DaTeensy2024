#include "GY-6500.h"
#include <math.h>

GY6500Sensor::GY6500Sensor(uint8_t deviceAddress, float alpha, float dt)
{
    this->deviceAddress = deviceAddress;
    this->alpha = alpha;
    this->dt = dt;
}

void GY6500Sensor::begin()
{
    Wire.begin();
    Wire.beginTransmission(deviceAddress);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0);
    Wire.endTransmission();
}

void GY6500Sensor::readData()
{
    accelX = readWord2C(0x3B); // ACCEL_XOUT_H register
    accelY = readWord2C(0x3D); // ACCEL_YOUT_H register
    accelZ = readWord2C(0x3F); // ACCEL_ZOUT_H register
    gyroX = readWord2C(0x43);  // GYRO_XOUT_H register
    gyroY = readWord2C(0x45);  // GYRO_YOUT_H register
    gyroZ = readWord2C(0x47);  // GYRO_ZOUT_H register

    calculateAngleSpeed();
}

float GY6500Sensor::getAngle()
{
    readData();
    return angle ? angle : -1;
}

float GY6500Sensor::getSpeed()
{
    readData();
    return speed ? speed : -1;
}

int16_t GY6500Sensor::readWord2C(uint8_t regAddress)
{
    Wire.beginTransmission(deviceAddress);
    Wire.write(regAddress);
    Wire.endTransmission(false);
    Wire.requestFrom(deviceAddress, 2, true);

    int16_t value = Wire.read() << 8 | Wire.read();
    if (value >= 0x8000)
    {
        value = -((65535 - value) + 1);
    }
    return value;
}

void GY6500Sensor::calculateAngleSpeed()
{
    // Convert raw accelerometer data to acceleration in g
    const float accelScaleFactor = 4.0 / 32768.0;
    float accelX_g = accelX * accelScaleFactor;
    float accelY_g = accelY * accelScaleFactor;
    float accelZ_g = accelZ * accelScaleFactor;

    // Convert raw gyroscope data to angular velocity in degrees/s
    const float gyroScaleFactor = 2000.0 / 32768.0;
    float gyroX_deg = gyroX * gyroScaleFactor;
    float gyroY_deg = gyroY * gyroScaleFactor;
    float gyroZ_deg = gyroZ * gyroScaleFactor;

    // Calculate total acceleration (excluding gravity)
    float accelTotal = sqrt(pow(accelX_g, 2) + pow(accelY_g, 2) + pow(accelZ_g, 2));

    // Calculate angle using complementary filter
    angle = alpha * (angle + gyroX_deg * dt) + (1 - alpha) * atan2(accelY_g, accelZ_g) * (180 / M_PI);

    // Calculate speed by integrating acceleration
    speed = accelTotal * dt;
}