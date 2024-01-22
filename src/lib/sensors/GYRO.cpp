
#include "GYRO.h"

GYRO::GYRO()
{
}
MPU9250 mpu; // You can also use MPU9255 as is

void GYRO::begin()
{
    Wire.begin();
    delay(1500);
    for (int i = 0; i < 3; i++)
    {
        if (!mpu.setup(0x68))
        { // change to your own address
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(5000);
        }
        else
        {
            break;
        }
    }
}

void GYRO::loop()
{
    if (mpu.update())
    {
        // if (millis() > lastUpdate + 25)
        // {
        data.yaw = mpu.getYaw();
        data.pitch = mpu.getPitch();
        data.roll = mpu.getRoll();
        data.accelX = mpu.getAccX();
        data.accelY = mpu.getAccY();
        data.accelZ = mpu.getAccZ();
        data.magX = mpu.getMagX();
        data.magY = mpu.getMagY();
        data.magZ = mpu.getMagZ();
        lastUpdate = millis();
        // }
    }
}

float GYRO::getYaw()
{
    return data.yaw;
}

float GYRO::getPitch()
{
    return data.pitch;
}

float GYRO::getRoll()
{
    return data.roll;
}

float GYRO::getAccelX()
{
    return data.accelX;
}

float GYRO::getAccelY()
{
    return data.accelY;
}

float GYRO::getAccelZ()
{
    return data.accelZ;
}

float GYRO::getMagX()
{
    return data.magX;
}

float GYRO::getMagY()
{
    return data.magY;
}

float GYRO::getMagZ()
{
    return data.magZ;
}

/* Comandos

bool setup(const uint8_t addr, const MPU9250Setting& setting, WireType& w = Wire);
void verbose(const bool b);
void ahrs(const bool b);
void sleep(bool b);
void calibrateAccelGyro();
void calibrateMag();
bool isConnected();
bool isConnectedMPU9250();
bool isConnectedAK8963();
bool isSleeping();
bool available();
bool update();
void update_accel_gyro();
void update_mag();
void update_rpy(float qw, float qx, float qy, float qz);

float getRoll() const;
float getPitch() const;
float getYaw() const;

float getEulerX() const;
float getEulerY() const;
float getEulerZ() const;

float getQuaternionX() const;
float getQuaternionY() const;
float getQuaternionZ() const;
float getQuaternionW() const;

float getAcc(const uint8_t i) const;
float getGyro(const uint8_t i) const;
float getMag(const uint8_t i) const;
float getLinearAcc(const uint8_t i) const;

float getAccX() const;
float getAccY() const;
float getAccZ() const;
float getGyroX() const;
float getGyroY() const;
float getGyroZ() const;
float getMagX() const;
float getMagY() const;
float getMagZ() const;
float getLinearAccX() const;
float getLinearAccY() const;
float getLinearAccZ() const;

float getAccBias(const uint8_t i) const;
float getGyroBias(const uint8_t i) const;
float getMagBias(const uint8_t i) const;
float getMagScale(const uint8_t i) const;

float getAccBiasX() const;
float getAccBiasY() const;
float getAccBiasZ() const;
float getGyroBiasX() const;
float getGyroBiasY() const;
float getGyroBiasZ() const;
float getMagBiasX() const;
float getMagBiasY() const;
float getMagBiasZ() const;
float getMagScaleX() const;
float getMagScaleY() const;
float getMagScaleZ() const;

float getTemperature() const;

void setAccBias(const float x, const float y, const float z);
void setGyroBias(const float x, const float y, const float z);
void setMagBias(const float x, const float y, const float z);
void setMagScale(const float x, const float y, const float z);
void setMagneticDeclination(const float d);

void selectFilter(QuatFilterSel sel);
void setFilterIterations(const size_t n);

bool selftest();
*/