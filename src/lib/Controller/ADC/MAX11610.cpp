#include "MAX11610.h"

MAX11610::MAX11610(uint8_t address, int I2CPort, TCA9548A *tca)
{
  _address = address;
  _I2CPORT = I2CPort;
  _tca = tca;
  // _address = 0x33;
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

  Wire.requestFrom(_address, static_cast<size_t>(2));
  uint16_t value = (Wire.read() << 8) | Wire.read();
  Wire.endTransmission();
  
  return value;
}

uint16_t MAX11610::readADC(uint8_t channel)
{

  _tca->pcaselect(_I2CPORT);
  
  // The MAX11610 uses channel configuration register 0x08 to set the desired channel
  writeRegister(0x08, channel);
  // The ADC result is read from register 0x00 and 0x01 (16-bit data)
  return readRegister(0x00);
}

int MAX11610::readADC1(){  return readADC(0x01);  }
int MAX11610::readADC0(){  return readADC(0x00);  }
int MAX11610::readADC2(){  return readADC(0x02);  }
int MAX11610::readADC3(){  return readADC(0x03);  }
int MAX11610::readADC4(){  return readADC(0x04);  }
int MAX11610::readADC5(){  return readADC(0x05);  }
int MAX11610::readADC6(){  return readADC(0x06);  }
int MAX11610::readADC7(){  return readADC(0x07);  }
int MAX11610::readADC8(){  return readADC(0x08);  }
int MAX11610::readADC9(){  return readADC(0x09);  }
int MAX11610::readADC10(){  return readADC(0x0A);  }

