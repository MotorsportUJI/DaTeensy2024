#include "Data.h"

Data::Data(unsigned long intervalValue, HardwareSerial &telemetryUART,  Display *displayObj)
{   
    // Creamos el objeto teleemtria
    TELEMETRY telemetryTemp(telemetryUART);

    // Creamos el objeto SD
    SDStore tempSD;


    numSensors = 0;
    previousMillis = 0;

    // guardamos en el objeto DATA los objetos Telemetry, SDStore y pantalla
    telemetry = telemetryTemp;
    sdstore = tempSD;
    display = displayObj;
    
    // guardamos el intervalo de tiempo para enviar datos
    interval = intervalValue;
}

void Data::init()
{
    // sdstore.initSD();
    telemetry.init();
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
        String value = sensors[i]->read();
        dataStr += value;
        if (i < numSensors - 1)
        {
            dataStr += ", ";
        }
    }

    return dataStr;
}

String Data::getTelemetry()
{
    String dataStr = "";

    for (int i = 0; i < numSensors; i++)
    {
        if (sensors[i]->sendTelemetry == true)
        {
            String value = sensors[i]->read();
            dataStr += value;
            if (i < numSensors - 1)
            {
                dataStr += ", ";
            }
        }
    }
    // check if the last character is a comma
    if (dataStr[dataStr.length() - 1] == ',')
    {
        dataStr.remove(dataStr.length() - 1);
    }
    return dataStr;
}

String Data::getRaw()
{
    String dataStr = "";

    for (int i = 0; i < numSensors; i++)
    {
        String value = sensors[i]->readRaw();
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

        String data = getTelemetry();
        Serial.println(data);
        // sdstore.saveLine(data);
        telemetry.sendData(data);

        // foreach sensor
        for (int i = 0; i < numSensors; i++)
        {
            display->sendSensorData(*sensors[i]);
            if (debug)
            {
                Serial.print((String) "[" + i + "]" + sensors[i]->getName() + "\t");
                if (i % 5 == 0)
                {
                    Serial.println();
                }
            }
        }
        if (debug)
        {

            // Serial.println(data + "\n\n");
            delay(1000);
        }
        previousMillis = currentMillis;
    }
}
