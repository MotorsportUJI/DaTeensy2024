#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>
#include <CRC32.h>
#include <HardwareSerial.h>

class TELEMETRY
{
public:
    typedef struct Packet
    {
        uint32_t rpm;
        uint32_t crc;
        uint32_t end;
    } Packet;

    TELEMETRY();
    TELEMETRY(HardwareSerial &serial);
    void init();
    void sendPacket(Packet packet);
    void sendData(String data);

private:
    HardwareSerial *ser1;
};

#endif
