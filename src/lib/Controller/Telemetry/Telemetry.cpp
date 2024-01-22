#include "Telemetry.h"

TELEMETRY::TELEMETRY() { ser1 = &Serial5; }

// FIXME: Not working with serial from settings.h
TELEMETRY::TELEMETRY(HardwareSerial &_serial)
{
    this->ser1 = &_serial;
}

void TELEMETRY::init()
{
    this->ser1->begin(115200);
    // ser1->println("Telemetry initialized");
    // Serial.println("Telemetry initialized");
}

void TELEMETRY::sendPacket(Packet packet)
{
    packet.crc = CRC32::calculate(&packet, sizeof(Packet) - sizeof(uint32_t));
    packet.end = 0x0f0f0f0f;

    this->ser1->write((uint8_t *)&packet, sizeof(packet));
}

void TELEMETRY::sendData(String data)
{
    this->ser1->println(data);
}
