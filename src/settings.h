#ifndef SETTINGS
#define SETTINGS

#define ScreenUART Serial8
#define TelemetryUART Serial7

#define EEPROM_time_base_address 0
#define EEPROM_fss_base_address 4

#define CAN CAN3
#define DEBUG

#define PI 3.1415926535897932384626433832795


// reading 1 from this pin means that the cable is connected to GND, reading 0 means that is disconnected

#define DEBUG_LED 12

// Buttons
#define B1 15   // change screen
#define B2 14   // cambiar efecto leds
#define B3 41   // cambiar mde donde viene los datos (TPS. RPM, etc)
#define B4 40   

// GY-6500 or GY-9250 sensor addresses and registers
#define BUS = smbus.SMBus(1)

#define DEVICE_ADDRESS 0x68 // Replace with the actual sensor address
#define PWR_MGMT_1 0x6B
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43



// Sensor configuration
// #define ACCEL_CONFIG 0x08 // Set accelerometer range to +/- 4g
// #define GYRO_CONFIG 0x18  // Set gyroscope range to +/- 2000 degrees/s

// Complementary filter constants
#define ALPHA 0.98 // Weight for gyroscope data
#define DT 0.01    // Time interval between sensor readings

// ADC
#define ADC_CS_PIN 10

// Termopar sensor
#define SCK_PIN 6 // Replace with the appropriate pin numbers
#define CS_PIN 7
#define SO_PIN 8
#define FIREWALL_CS_PIN 10
#define RADIADOR_CS_PIN 36
#define ACEITE_CS_PIN 37

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
#define FUEL_PRESSURE_PIN 15
#define FUEL_PRESSURE_MIN 0
#define FUEL_PRESSURE_MAX 1023
#define FUEL_PRESSURE_MIN_BAR 0
#define FUEL_PRESSURE_MAX_BAR 13

// Oil preasure sensor
#define OIL_PRESSURE_PIN A5
#define OIL_PRESSURE_MIN 0
#define OIL_PRESSURE_MAX 1023
#define OIL_PRESSURE_MIN_BAR 0
#define OIL_PRESSURE_MAX_BAR 10

// TODO Admission

#define MIN_ADMISSION 0
#define MAX_ADMISSION 100

#define MIN_ADMISSION_BAR 0
#define MAX_ADMISSION_BAR 100

// TODO Calderin

#define MIN_CALDERIN 0
#define MAX_CALDERIN 100
#define MIN_CALDERIN_BAR 0
#define MAX_CALDERIN_BAR 100

// Relé

#define RELAY_PIN 2

// Hall

#define HALL_PIN 9

#endif