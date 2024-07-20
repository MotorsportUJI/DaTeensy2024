// #include "lib/CAN/OBD2.h"
// #include "lib/Controller/Sensors/Sensors.h"
// #include "lib/Controller/ADC/MAX11610.h"
// #include "lib/sensors/gear.h"
// // Termopar snesor
// #include "lib/sensors/max6675_sensor.h"
// // Gyro sensor
// #include "lib/sensors/GYRO.h"
// // I2C Mux
// #include "lib/Controller/I2CMux/TCA9548A.h"
// // ADC
// #include "lib/Controller/ADC/MAX11610.h"

// // MUX
// #include "lib/Controller/MUX/CD74HC4067SM96.h"


// /**----------------------
//  *    OBD
//  *------------------------**/
// OBD2::OBD2sensordata OBD2db = {0};


// /**----------------------
//  *    MUX TCA (I2C)
//  *------------------------**/
// TCA9548A tca;

// /**----------------------
//  *    MUX  (Normal)
//  *------------------------**/
// CD74HC4067SM96 mux;

// int readPin0() {return mux.read0();}
// int readPin1() {return mux.read1();}
// int readPin2() {return mux.read2();}
// int readPin3() {return mux.read3();}
// int readPin4() {return mux.read4();}
// int readPin5() {return mux.read5();}
// int readPin6() {return mux.read6();}
// int readPin7() {return mux.read7();}

// /**----------------------
//  *    Gyro
//  *------------------------**/

// GYRO bnoGyro(&tca);

// float getax() { return bnoGyro.getAccelX(); }
// float getay() { return bnoGyro.getAccelY(); }
// float getaz() { return bnoGyro.getAccelZ(); }
// float getYaw() { return bnoGyro.getYaw(); }
// float getPitch() { return bnoGyro.getPitch(); }
// float getRoll() { return bnoGyro.getRoll(); }
// float getGyroX() { return bnoGyro.getGyroX(); }
// float getGyroY() { return bnoGyro.getGyroY(); }
// float getGyroZ() { return bnoGyro.getGyroZ(); }


// Sensor BNOAccelX("Gyro AccelX", VALUE, getax, "m/s2", true, true, "accel_x", true);
// Sensor BNOAccelY("Gyro AccelY", VALUE, getay, "m/s2", true, true, "accel_y", true);
// Sensor BNOAccelZ("Gyro AccelZ", VALUE, getaz, "m/s2", true, true, "accel_z", true);
// Sensor BNOYaw("Gyro Yaw", VALUE, getYaw, "º", true, true, "gyro_yaw", true);
// Sensor BNOPitch("Gyro Pitch", VALUE, getPitch, "º", true, true, "gyro_pitch", true);
// Sensor BNORoll("Gyro Roll", VALUE, getRoll, "º", true, true, "gyro_roll", true);
// Sensor BNOGyroX("Gyro X", VALUE, getGyroX, "rad/s", true, true, "gyro_angle_x", true);
// Sensor BNOGyroY("Gyro Y", VALUE, getGyroY, "rad/s", true, true, "gyro_angle_y", true);
// Sensor BNOGyroZ("Gyro Z", VALUE, getGyroZ, "rad/s", true, true, "gyro_angle_z", true);



// /**----------------------
//  *    Termopar
//  *------------------------**/
// MAX6675Sensor max6675(SCK_PIN, CS_PIN, SO_PIN);


// /**----------------------
//  *    ADC 1
//  *------------------------**/
// MAX11610 adc1(0x33, 2, &tca);

// float readADC10(){    return adc1.readADC0();   }
// float readADC11(){    return adc1.readADC1();   }
// float readADC12(){    return adc1.readADC2();   }
// float readADC13(){    return adc1.readADC3();   }
// float readADC14(){    return adc1.readADC4();   }
// float readADC15(){    return adc1.readADC5();   }
// float readADC16(){    return adc1.readADC6();   }
// float readADC17(){    return adc1.readADC7();   }
// float readADC18(){    return adc1.readADC8();   }
// float readADC19(){    return adc1.readADC9();   }
// float readADC110(){    return adc1.readADC10();   }

// Sensor TPS2("TPS2", VALUE, readADC10, "V", false, false, "tps2", true);
// Sensor PresionCombustible("PresionCombustible", MAPPING, readADC11, FUEL_PRESSURE_MIN, FUEL_PRESSURE_MAX, FUEL_PRESSURE_MIN_BAR, FUEL_PRESSURE_MAX_BAR, "bar", false, true, "fuel_p", true);
// Sensor CaudalAire("CaudalAire", VALUE, readADC12, "V", false, false, "airflow", true);
// Sensor libre1("libre1", VALUE, readADC13, "V", false, false, "libre1", true);
// Sensor libre2("libre2", VALUE, readADC14, "V", false, false, "libre2", true);
// Sensor libre3("libre3", VALUE, readADC15, "V", false, false, "libre3", true);
// Sensor PresionFreno("PresionFreno", VALUE, readADC16, "V", false, false, "brake_p", true);
// Sensor SuspensionFrontRight("Suspension delantera derecha", SUSPENSION, readADC17, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, false, "susp_f_r", true);
// Sensor SuspensionFrontLeft("Suspension delantera izquierda", SUSPENSION, readADC18, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, false, "susp_f_l", true);
// Sensor SuspensionRearRight("Suspension trasera derecha", SUSPENSION, readADC19, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, false, "susp_r_r", true);
// Sensor SuspensionRearLeft("Suspension trasera izquierda", SUSPENSION, readADC110, MIN_SUSPENSION, MAX_SUSPENSION, MIN_SUSPENSION_MM, MAX_SUSPENSION_MM, "mm", false, false, "sus_r_l", true);


// /**----------------------
//  *    ADC 2
//  *------------------------**/
// MAX11610 adc2(0x34, 3, &tca);

// float readADC20 (){ return adc2.readADC0(); }
// float readADC21 (){ return adc2.readADC1(); }
// float readADC22 (){ return adc2.readADC2(); }
// float readADC23 (){ return adc2.readADC3(); }
// float readADC24 (){ return adc2.readADC4(); }


// Sensor PAireAdmision2FPB("Presion de aire de admision", MAPPING, readADC20, MIN_ADMISSION, MAX_ADMISSION, MIN_ADMISSION_BAR, MAX_ADMISSION_BAR, "bar", false, false, "adm_p", true);
// Sensor PCalderinFPB("Presion del calderin", MAPPING, readADC21, MIN_CALDERIN, MAX_CALDERIN, MIN_CALDERIN_BAR, MAX_CALDERIN_BAR, "bar", false, false, "calder_p", true);
// Sensor OilPressure("Presion aceite", MAPPING, readADC22, OIL_PRESSURE_MIN, OIL_PRESSURE_MAX, OIL_PRESSURE_MIN_BAR, OIL_PRESSURE_MAX_BAR, "bar", false, false, "oil_p", true);
// // TODO Sensores FPB


// /**----------------------
//  *    Gear 
//  *------------------------**/
// Sensor Gear("Gear", VALUE, GEAR::getGear, "gear", false, true, "gear", true);











// /**----------------------
//  *    Normal sensors
//  *------------------------**/


// Sensor TFirewall("T. Firewall", TEMPERATURE, max6675.readTemperature(), "ºC", "tempFirewall", true);
// Sensor TRadiador("T. Radiador", TEMPERATURE, max6675.readTemperature(), "ºC", "tempRadiador", true);
// Sensor Taceite("T. Aceite", TEMPERATURE, max6675.readTemperature(), "ºC", "tempAceite", true);



// /**----------------------
//  *    Freno
//  *------------------------**/
// Sensor BrakePreassure("PresionFreno", VALUE, OBD2::getIntakeManifoldAbsPressure, "kPa", false, true, "presIntake", true);

// /**----------------------
//  *    Hall (Velocidad)
//  *------------------------**/
// Sensor HallSpeedLeft("VelocidadIzq", VALUE, OBD2::getSpeed, "km/h", false, true, "speed", true);
// Sensor HallSpeedRight("VelocidadDer", VALUE, OBD2::getSpeed, "km/h", false, true, "speed", true);



// /**----------------------
//  *    ODB Sensors
//  *------------------------**/

// Sensor ODBRpm("RPM", VALUE, OBD2::getRPM, "RPM", false, true, "rpm", true);
// Sensor ODBCoolantTemp("Temperatura refrigerante", VALUE, OBD2::getEngineCoolantTemp, "ºC", false, true, "watertemp", true);
// Sensor ODBAirTemp("Temperatura aire", VALUE, OBD2::getAirIntakeTemp, "ºC", false, true, "airtemp", true);
// Sensor ODBThrottle("TPS abs", VALUE, OBD2::getObdTPS, "%", true, true, "throttle", true);
// Sensor ODBThrottleRel("TPS rel", VALUE, OBD2::getRelativeThrottlePosition, "%", true, true, "throttlerel", true);

// Sensor ODBAbsPressure("Presion absoluta", VALUE, OBD2::getBarometricPressure, "kPa", false, false, "abspressure", true);
// Sensor ODBIntakePressure("Presion admFion", VALUE, OBD2::getIntakeManifoldAbsPressure, "kPa", false, true, "presIntake", true);
// Sensor ODBDTCCount("DTC", VALUE, OBD2::getDTC, "DTC", false, false, "dtc", true);

// Sensor ODBVoltage("Voltaje", VALUE, OBD2::getControlModuleVoltage, "V", true, true, "voltage", true);
// Sensor ODBEngineLoad("Carga motor", VALUE, OBD2::getEngineLoad, "%", true, false, "engineload", true);
// // sendFuelSystemStatus(OBD2db.fuel_system_status);

// Sensor ODBTrim("Trim", VALUE, OBD2::getLongTermFuelTrim, "%", true, false, "FT", true);
// Sensor ODB02Trim("Trim O2", VALUE, OBD2::getOxygenSensorFuelTrim, "%", true, false, "O2trim", true);
// Sensor ODB02Volt("Voltaje O2", VALUE, OBD2::getOxygenSensorVoltage, "V", true, false, "O2v", true);

// Sensor ODBTimingAdvance("Avance", VALUE, OBD2::getTimingAdvance, "º", false, false, "Tadv", true);

// // TODO Donde van?
// /**---------------------- 
//  *    Sensor direccion
//  *------------------------**/
// Sensor SteeringAngle("AnguloDireccion", VALUE, OBD2::getSpeed, "km/h", false, true, "speed", true);