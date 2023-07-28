#ifndef SETTINGS
#define SETTINGS

#define ScreenUART Serial8
#define TelemetryUART Serial7

#define EEPROM_time_base_address 0
#define EEPROM_fss_base_address 4

#define CAN CAN3
#define DEBUG

// reading 1 from this pin means that the cable is connected to GND, reading 0 means that is disconnected

#define DEBUG_LED 12

#define GREEN_BUTTON 40 // clear dtc
#define RED_BUTTON 41   // switch screen view

// GY-6500 or GY-9250 sensor addresses and registers
#define BUS = smbus.SMBus(1)

#define DEVICE_ADDRESS 0x68 // Replace with the actual sensor address
#define PWR_MGMT_1 0x6B
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43

// Sensor configuration
#define ACCEL_CONFIG 0x08 // Set accelerometer range to +/- 4g
#define GYRO_CONFIG 0x18  // Set gyroscope range to +/- 2000 degrees/s

// Complementary filter constants
#define ALPHA 0.98 // Weight for gyroscope data
#define DT 0.01    // Time interval between sensor readings

// ADC
#define ADC_CS_PIN 10

// Termopar sensor
#define SCK_PIN 6 // Replace with the appropriate pin numbers
#define CS_PIN 7
#define SO_PIN 8

// suspension sensors pins
#define SUSPENSION_FRONT_LEFT_PIN A0
#define SUSPENSION_FRONT_RIGHT_PIN A1
#define SUSPENSION_REAR_LEFT_PIN A2
#define SUSPENSION_REAR_RIGHT_PIN A3

#define MIN_SUSPENSION 0
#define MAX_SUSPENSION 1023
#define MIN_SUSPENSION_MM 0
#define MAX_SUSPENSION_MM 70

// Fuel preasure sensor
#define FUEL_PRESSURE_PIN A4
#define FUEL_PRESSURE_MIN 0
#define FUEL_PRESSURE_MAX 1023
#define FUEL_PRESSURE_MIN_BAR 0
#define FUEL_PRESSURE_MAX_BAR 10

// Oil preasure sensor
#define OIL_PRESSURE_PIN A5
#define OIL_PRESSURE_MIN 0
#define OIL_PRESSURE_MAX 1023
#define OIL_PRESSURE_MIN_BAR 0
#define OIL_PRESSURE_MAX_BAR 10

#endif