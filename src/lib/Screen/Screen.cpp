#include "Screen.h"

Display::Display(HardwareSerialIMXRT &_serial)
{
    this->serialScreen = &_serial;
}

void Display::init()
{
    this->serialScreen->begin(57600);
    // serialScreen->begin(19200);
    void *buffer = malloc(1024);

    this->serialScreen->addMemoryForWrite(buffer, 1024);

    // this->serialScreen->print("bauds=921600");
}

void Display::rpmled(int nleds)
{
    switch (nleds)
    {
    case 0:
        analogWrite(33, 0);
        break;
    case 1:
        analogWrite(33, 10);
        break;
    case 2:
        analogWrite(33, 25);
        break;
    case 3:
        analogWrite(33, 43);
        break;
    case 4:
        analogWrite(33, 55);
        break;
    case 5:
        analogWrite(33, 74);
        break;
    case 6:
        analogWrite(33, 87);
        break;
    case 7:
        analogWrite(33, 100);
        break;
    case 8:
        analogWrite(33, 117);
        break;
    case 9:
        analogWrite(33, 130);
        break;
    case 10:
        analogWrite(33, 150);
        break;
    }
}

void Display::rpmledInverse(int nleds)
{
    switch (nleds)
    {
    case 0:
        analogWrite(33, 255);
        break;
    case 1:
        analogWrite(33, 135);
        break;
    case 2:
        analogWrite(33, 120);
        break;
    case 3:
        analogWrite(33, 110);
        break;
    case 4:
        analogWrite(33, 87);
        break;
    case 5:
        analogWrite(33, 74);
        break;
    case 6:
        analogWrite(33, 55);
        break;
    case 7:
        analogWrite(33, 40);
        break;
    case 8:
        analogWrite(33, 30);
        break;
    case 9:
        analogWrite(33, 10);
        break;
    case 10:
        analogWrite(33, 0);
        break;
    }
}

void Display::endMessage()
{
    byte a = 0xff;
    for (int i = 0; i < 3; i++)
    {
        this->serialScreen->write(a);
    }
}

// FIXME: En el cambio de gear, se debe enviar el valor de gear anterior, salvo que se quede en 255 por mas de 1 segundo
void Display::sendGear(int str, bool desired)
{

    if (str == 255)
    {
        this->serialScreen->printf("%s%s%s", "gear", (desired ? "" : "2"), ".txt =\"E\"");
        Display::endMessage();
        return;
    }

    this->serialScreen->printf("%s%s%s", "gear", (desired ? "" : "2"), ".txt =\"E\"");
    Display::endMessage();
}

void Display::sendFuelSystemStatus(int sta)
{
    char tosend[32];
    ;
    if (sta == 0)
    {
        char yeah[] = "ENGINE OFF";
        strcpy(tosend, yeah);
    }
    else if (sta == 1)
    {
        char yeah[] = "OPEN LOOP \\rNO ENOUGH\\rTEMP";
        strcpy(tosend, yeah);
    }
    else if (sta == 2)
    {
        char yeah[] = "CLOSED \\r LOOP";
        strcpy(tosend, yeah);
    }
    else if (sta == 4)
    {
        char yeah[] = "OPEN LOOP\\rDUE \\rfuel ct decel";
        strcpy(tosend, yeah);
    }
    else if (sta == 8)
    {
        char yeah[] = "OPEN LOOP\\rSYSTEM \\rFAILURE";
        strcpy(tosend, yeah);
    }
    else if (sta == 16)
    {
        char yeah[] = "CLOSED \\rLOOP\\rWITH FAULTS";
        strcpy(tosend, yeah);
    }

    // Serial.printf("fss.txt=\"%s\"\n",tosend);
    this->serialScreen->printf("fss.txt=\"%s\"", tosend);
    Display::endMessage();
}

void Display::sendTimeEngineOn(uint32_t str)
{
    uint32_t hours = str / 3600;
    uint32_t minutes = (str - hours * 3600) / 60;
    uint32_t seconds = (str - hours * 3600 - minutes * 60);
    this->serialScreen->printf("time.txt=\"%d:%d:%d\"", hours, minutes, seconds);
    Display::endMessage();
}

#define __disable_irq() __asm__ volatile("CPSID i" :: \
                                             : "memory");
#define __enable_irq() __asm__ volatile("CPSIE i" :: \
                                            : "memory");

void Display::sendSensorData(Sensor &sensor)
{

    this->serialScreen->printf(sensor.getScreenValue().c_str());
    // Serial.println(sensor.getScreenValue().c_str());
    Display::endMessage();
}

/**----------------------
 *    Screen set
 *------------------------**/

void Display::setMainScreen()
{
    // this->serialScreen->printf("page 1"); // page 1 is yet to be populated
    this->serialScreen->printf("page 1");
    Display::endMessage();
}

void Display::setSensorScreen()
{
    this->serialScreen->printf("page 2");
    Display::endMessage();
}

void Display::setSplashScreen()
{
    this->serialScreen->printf("page 0");
    Display::endMessage();
}

void Display::setDebugScreen()
{
    this->serialScreen->printf("page 3");
    Display::endMessage();
}
