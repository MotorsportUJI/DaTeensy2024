#include "Telemetry.h"

TELEMETRY::TELEMETRY() { ser1 = &Serial5; }
TELEMETRY::TELEMETRY(HardwareSerial &serial) : ser1(&serial) {}

void TELEMETRY::init()
{
    ser1->begin(115200);
}

void TELEMETRY::sendPacket(Packet packet)
{
    packet.crc = CRC32::calculate(&packet, sizeof(Packet) - sizeof(uint32_t));
    packet.end = 0x0f0f0f0f;

    ser1->write((uint8_t *)&packet, sizeof(packet));
}

void TELEMETRY::sendData(String data)
{
    ser1->println(data);
}
