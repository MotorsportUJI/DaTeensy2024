#include "MAX11610.h"

MAX11610::MAX11610()
{
  // Initialize with default I2C slave address
  _address = 0x68;
  Wire.begin();
}

void MAX11610::writeRegister(uint8_t reg, uint8_t value)
{
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint16_t MAX11610::readRegister(uint8_t reg)
{
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(_address, 2);
  uint16_t value = (Wire.read() << 8) | Wire.read();
  return value;
}

uint16_t MAX11610::readADC(uint8_t channel)
{
  // The MAX11610 uses channel configuration register 0x08 to set the desired channel
  writeRegister(0x08, channel);
  // The ADC result is read from register 0x00 and 0x01 (16-bit data)
  return readRegister(0x00);
}
