#include "Data.h"

Data::Data(unsigned long intervalValue, TELEMETRY telemetryObj, SDStore sdstoreObj)
{
    numSensors = 0;
    previousMillis = 0;

    telemetry = telemetryObj;
    sdstore = sdstoreObj;

    telemetry.init();
    sdstore.initSD();
    interval = intervalValue;
}

void Data::addSensor(Sensor *sensor)
{
    if (numSensors < MAX_SENSORS)
    {
        sensors[numSensors] = sensor;
        numSensors++;
    }
    else
    {
        Serial.println("No se pueden agregar más sensores. Se alcanzó el límite máximo.");
    }
}

String Data::get()
{
    String dataStr = "";

    for (int i = 0; i < numSensors; i++)
    {
        float value = sensors[i]->read();
        dataStr += String(value);
        if (i < numSensors - 1)
        {
            dataStr += ", ";
        }
    }

    return dataStr;
}

String Data::getRaw()
{
    String dataStr = "";

    for (int i = 0; i < numSensors; i++)
    {
        float value = sensors[i]->readRaw();
        dataStr += String(value);
        if (i < numSensors - 1)
        {
            dataStr += ", ";
        }
    }

    return dataStr;
}

String Data::getFull()
{
    String dataStr = "";

    for (int i = 0; i < numSensors; i++)
    {
        dataStr += sensors[i]->readFull();

        if (i < numSensors - 1)
        {
            dataStr += "\n";
        }
    }

    return dataStr;
}

void Data::loop()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {

        String data = get();
        sdstore.saveLine(data);
        telemetry.sendData(data);

        previousMillis = currentMillis;
    }
}
