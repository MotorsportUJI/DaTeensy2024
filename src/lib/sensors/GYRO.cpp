
#include "GYRO.h"

GYRO::GYRO()
{
}
BNO08x myIMU;

void GYRO::begin() // Give I2C address and start sensorv 0x68, config
{
    Wire.begin();

    // if (myIMU.begin() == false){
    // Setup without INT/RST control (Not Recommended)
    if (myIMU.begin(BNO08X_ADDR, Wire, BNO08X_INT, BNO08X_RST) == false)
    {
#ifdef GYRO_H_DEBUG
        Serial.println("BNO08x: BNO08x not detected at default I2C address. Check your jumpers on the hookup guide. Freezing...");
#endif
        while (1)
            ;
    }
    else
    {
#ifdef GYRO_H_DEBUG
        Serial.println("BNO08x: Found!!");
#endif
    }
    setReports();
    calibrate();
}

void GYRO::loop() // Get values from gyroscope
{
    bool updated = false;

    if (myIMU.wasReset())
    {
#ifdef GYRO_H_DEBUG
        Serial.println("BNO08x: Sensor was reset");
#endif
        setReports();
    }

    if (myIMU.getSensorEvent() == true)
    {
        // Accel
        if (myIMU.getSensorEventID() == SENSOR_REPORTID_ACCELEROMETER)
        { // m / s2
            data.accelX = myIMU.getAccelX();
            data.accelY = myIMU.getAccelY();
            data.accelZ = myIMU.getAccelZ();
            updated = true;
        }

        // Euler
        else if (myIMU.getSensorEventID() == SENSOR_REPORTID_ROTATION_VECTOR)
        { // quaternion -> degree
            data.roll = (myIMU.getRoll()) * 180.0 / PI;
            data.pitch = (myIMU.getPitch()) * 180.0 / PI;
            data.yaw = (myIMU.getYaw()) * 180.0 / PI;
            updated = true;
        }

        if (updated)
        {
            lastUpdate = millis();
        }

#ifdef GYRO_H_DEBUG
        printDataDebug();
#endif
    }
}

void GYRO::calibrate()
{
    Serial.print("Calibrando BNO...  ");
    if (myIMU.clearTare())
    {
        Serial.print("[Clear Tare]...  ");
    }
    else
    {
        Serial.print("[Clear Tare]... ");
    }
    if (myIMU.tareNow())
    {
        Serial.print("[TareXYZ]...  ");
    }
    else
    {
        Serial.print("[TareXYZ]... ");
    }
    if (myIMU.saveTare())
    {
        Serial.print("[Save Tare]...  ");
    }
    else
    {
        Serial.print("[Save Tare]... ");
    }

    Serial.println("OK");
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

float GYRO::getGyroX()
{
    return data.gyroX;
}
float GYRO::getGyroY()
{
    return data.gyroY;
}
float GYRO::getGyroZ()
{
    return data.gyroZ;
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

void GYRO::setReports(void)
{
#ifdef GYRO_H_DEBUG
    Serial.println("BNO08x: Setting desired reports...");
#endif
   

    if (myIMU.enableAccelerometer())
    {
#ifdef GYRO_H_DEBUG
        Serial.println("Accelerometer enabled");
        Serial.println("Output in form x, y, z in m/s^2");
#endif
    }
    else
    {
#ifdef GYRO_H_DEBUG
        Serial.println("Could not enable accelerometer");
#endif
    }

    if (myIMU.enableRotationVector())
    {
#ifdef GYRO_H_DEBUG
        Serial.println(F("Rotation vector enabled"));
        Serial.println(F("Output in form roll, pitch, yaw"));
#endif
    }
    else
    {
#ifdef GYRO_H_DEBUG
        Serial.println("Could not enable rotation vector");
#endif
    }
}

void GYRO::printDataDebug()
{
    Serial.print("Accel: ");
    Serial.print(data.accelX);
    Serial.print(", ");
    Serial.print(data.accelY);
    Serial.print(", ");
    Serial.println(data.accelZ);



    Serial.print("Euler: ");
    Serial.print(data.roll);
    Serial.print(", ");
    Serial.print(data.pitch);
    Serial.print(", ");
    Serial.println(data.yaw);
    // delay(50);
}

/* Comandos anterior gyro (MPU)

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