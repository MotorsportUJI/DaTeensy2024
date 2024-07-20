#include "Termopar.h"

Termopar::Termopar(int sckPin, int csPin, int soPin, SPIMux *mux, int muxIndex)
    : max6675(sckPin, csPin, soPin) // inicialización lista de miembros para MAX6675
{
    this->sckPin = sckPin;
    this->csPin = csPin;
    this->soPin = soPin;
    this->_mux = mux;
    this->muxIndex = muxIndex;

    _mux->select(muxIndex);
}


float Termopar::readTemperature()
{
    _mux->select(muxIndex);
    return max6675.readCelsius();
}
