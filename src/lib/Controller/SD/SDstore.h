#ifndef SDSTORE_H
#define SDSTORE_H

#include <Arduino.h>
#include <SD.h>
#include "lib/persistence/persistance.h"

class SDStore
{
public:
    void initSD();
    void saveLine(String data);

private:
    String storeFile;
    void generateFileName();
};

#endif
