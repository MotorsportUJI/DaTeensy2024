#include "gear.h"
namespace GEAR {
  void initGear(){
      for(int i=0; i<7; i++){
        pinMode(i, INPUT);
      }
  }

  int getGear(){
    if (!digitalRead(0)){
      return 0;
    } else if (!digitalRead(1)){
      return 5;
    } else if (!digitalRead(2)){
      return 3;
    } else if (!digitalRead(3)){
      return 4;
    } else if (!digitalRead(4)){
      return 1;
    } else if (!digitalRead(5)){
      return 6;
    } else if (!digitalRead(6)){
      return 2;
    }



    for(int i=0; i<7; i++){
      if (!digitalRead(i)){
        return 6-i;
      }
    }
    return 255;
  }

  uint8_t desired_gear = 128;
  uint8_t getDesiredGear(){
    return desired_gear;
  }

  void setDesiredGear(uint8_t gear){
    desired_gear = gear;
  }


}

