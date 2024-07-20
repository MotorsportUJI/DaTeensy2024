#ifndef CD74HC4067SM96_H
#define CD74HC4067SM96_H

#include <CD74HC4067.h>


class CD74HC4067SM96
{
public:
    CD74HC4067SM96();
    void init(int readPin, int pinS0, int pinS1, int pinS2, int pinS3);

    int readPin(int pin);

    int read0();
    int read1();
    int read2();
    int read3();
    int read4();
    int read5();
    int read6();
    int read7();

private:
    void changePin(int pin);

    int _readPin;
    CD74HC4067 _mux;
    
};

#endif
