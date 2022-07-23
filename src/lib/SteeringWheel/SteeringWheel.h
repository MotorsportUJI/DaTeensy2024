#ifndef STEERINGWHEEL
#define STEERINGWHEEL

#include <Arduino.h>
#include "lib/OBD2/OBD2.h"

void rpmled(int nleds);
void rpmledInverse(int nleds);

void initScreen(HardwareSerial &_serial);

void sendGear(int str);
void sendOil(bool str);
void sendRPM(int str);
void sendCOLTMP(float str);
void sendAIRTMP(float str);

void sendTPS(float str);
void sendTrim(float str);
void send02Trim(float str);
void sendDTCcount(int str);
void sendVoltage(float str);

void sendAbsPressure(int str);
void sendIntakePressure(int str);

void sendDTCDebugScreen(const uint16_t msg[], uint8_t length);

void setMainScreen();
void setSplashScreen();
void setDebugScreen();


void sendOBDdata(OBD2sensordata OBD2db);

#endif