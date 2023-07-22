#include "SteeringWheel.h"
HardwareSerial *ser;

Display::Display(HardwareSerial &_serial)
{
    ser = &_serial;
    ser->begin(57600);
    // ser->begin(19200);
    void *buffer = malloc(1024);

    ser->addMemoryForWrite(buffer, 1024);
    // ser->print("bauds=921600");
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
        ser->write(a);
    }
}

// FIXME: En el cambio de gear, se debe enviar el valor de gear anterior, salvo que se quede en 255 por mas de 1 segundo
void Display::sendGear(int str, bool desired = false)
{

    if (str == 255)
    {
        ser->printf("%s%s%s", "gear", (desired ? "" : "2"), ".txt =\"E\"");
        endMessage();
        return;
    }

    ser->printf("%s%s%s", "gear", (desired ? "" : "2"), ".txt =\"E\"");
    endMessage();
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
        char yeah[] = "OPEN LOOP\\rDUE TO\\rfuel cut decel";
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
    ser->printf("fss.txt=\"%s\"", tosend);
    endMessage();
}

void Display::sendTimeEngineOn(uint32_t str)
{
    uint32_t hours = str / 3600;
    uint32_t minutes = (str - hours * 3600) / 60;
    uint32_t seconds = (str - hours * 3600 - minutes * 60);
    ser->printf("time.txt=\"%d:%d:%d\"", hours, minutes, seconds);
    endMessage();
}

#define __disable_irq() __asm__ volatile("CPSID i" :: \
                                             : "memory");
#define __enable_irq() __asm__ volatile("CPSIE i" :: \
                                            : "memory");

void Display::sendSensorData(Sensor &sensor)
{
    ser->print(sensor.getScreenValue());
}

/**----------------------
 *    Screen set
 *------------------------**/

void Display::setMainScreen()
{
    // ser->printf("page 1"); // page 1 is yet to be populated
    ser->printf("page 2");
    endMessage();
}

void Display::setSensorScreen()
{
    ser->printf("page 2");
    endMessage();
}

void Display::setSplashScreen()
{
    ser->printf("page 0");
    endMessage();
}

void Display::setDebugScreen()
{
    ser->printf("page 3");
    endMessage();
}
