#include "SteeringWheel.h"
HardwareSerial* ser;

void rpmled(int nleds){
  switch (nleds){
    case 0:
    analogWrite(33,0);
    break;
    case 1:
    analogWrite(33, 10);
    break;
    case 2:
    analogWrite(33,25);
    break;
    case 3:
    analogWrite(33,43);
    break;
    case 4:
    analogWrite(33,55);
    break;
    case 5:
    analogWrite(33,74);
    break;
    case 6:
    analogWrite(33, 87);
    break;
    case 7:
    analogWrite(33,100);
    break;
    case 8:
    analogWrite(33,117);
    break;
    case 9:
    analogWrite(33,130);
    break;
    case 10:
    analogWrite(33,150);
    break;


  }
}

void rpmledInverse(int nleds){
  switch (nleds){
    case 0:
    analogWrite(33,255);
    break;
    case 1:
    analogWrite(33, 135);
    break;
    case 2:
    analogWrite(33,120);
    break;
    case 3:
    analogWrite(33,110);
    break;
    case 4:
    analogWrite(33,87);
    break;
    case 5:
    analogWrite(33,74);
    break;
    case 6:
    analogWrite(33, 55);
    break;
    case 7:
    analogWrite(33,40);
    break;
    case 8:
    analogWrite(33,30);
    break;
    case 9:
    analogWrite(33,10);
    break;
    case 10:
    analogWrite(33,0);
    break;


  }
}


void initScreen(HardwareSerial &_serial){
    ser = &_serial;
    ser->begin(115200);

}

void endMessage(){
    byte a = 0xff;
    for ( int i = 0; i < 3; i ++ ){
    ser->write(a);
    }
}


void sendGear(int str) {

    if (str == 255){
        ser->printf("gear.txt=\"E\"");
        endMessage();
        return;
    }
    
    ser->printf("gear.txt=\"%d\"",str);
    endMessage();
}

void sendRPM(int str) {
    
    ser->printf("rpm.txt=\"%d\"",str);
    endMessage();

}

void sendCOLTMP(float str) {
    
    ser->printf("watertemp.txt=\"%.2f\"",str);
    endMessage();

}

void sendAIRTMP(float str) {
    
    ser->printf("airtemp.txt=\"%.2f\"",str);
    endMessage();

}

void sendTPS(float str){
    uint8_t str_int = round(str);
    ser->printf("throttlebar.val=%d",str_int);
    endMessage();
    ser->printf("throttle.txt=\"%2f\"%",str);
    endMessage();

}

void sendTrim1(float str){
    ser->printf("minifold1.txt=\"%.3f\"",str);
    endMessage();

}

void sendTrim2(float str){
    ser->printf("minifold2.txt=\"%.3f\"",str);
    endMessage();
}

void sendDTCcount(int str){
    ser->printf("dtc.txt=\"%d\"",str);
    endMessage();
}

void sendPressure1(int str){
    ser->printf("presion1.txt=\"%d\"",str);
    endMessage();

}

void sendPressure2(int str){
    ser->printf("presion2.txt=\"%d\"",str);
    endMessage();

}


void setMainScreen(){
    ser->printf("page 1");
    endMessage();
}

void setSplashScreen(){
    ser->printf("page 0");
    endMessage();

}

void setDebugScreen(){
    ser->printf("page 2");
    endMessage();
}

void sendDebugmsg(int msg, const char* debugstring){
    //Serial.printf("msg%d.txt=\"%s\"",msg,debugstring);
    ser->printf("msg%d.txt=\"%s\"",msg,debugstring);
    endMessage();
}

void sendDTCDebugScreen(const uint16_t msg[], uint8_t length){
    for(int i = 0; i<length; i++)
    //Serial.printf("%#x ", msg[i]);
    //Serial.println();
    for (int i = 0; i < length; i++){
        const char* yeah = getDTCstring(msg[i]);
        if (yeah != NULL){
            sendDebugmsg(i, yeah);
        } else{
        char yeah2[16];
        sprintf(yeah2, "%x",msg[i]);
        sendDebugmsg(i, yeah);
        }

        if (i >= 7){
            break;
        }
    }

}

void sendOBDdata(OBD2sensordata OBD2db){
    // update screen
    sendRPM(OBD2RPM(OBD2db));
    sendCOLTMP(OBD2TMP(OBD2db.Engine_coolant_temperature));
    sendAIRTMP(OBD2TMP(OBD2db.intake_air_temperature));
    sendTPS(OBD2PC(OBD2db.relavite_throttle_position));
    //sendTrim1(OBD2Trim(OBD2db.long_term_fuel_trim));
    //sendTrim2(OBD2Trim(OBD2db.oxygen_sensor_long_term_fuel_trim));
    sendPressure1(OBD2db.absolute_barometric_presure);
    sendPressure2(OBD2db.intake_manifold_absolute_pressure);
    sendDTCcount(OBD2db.DTC_CNT);
    
}