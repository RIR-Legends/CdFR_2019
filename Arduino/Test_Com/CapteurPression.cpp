#include "CapteurPression.h"

int CapteurPression::PRESSION = CAPTEURPREPIN;

CapteurPression::CapteurPression(){
  
}

int CapteurPression::GetPression(){
  int pression = 0;
  int sommePression = 0;
  int index = 1;
  for(index = 1; index < 10; index++){
    pression = analogRead(PRESSION);
    if(pression < 10){
      sommePression++;
    }
    delay(5);
  }
  if(sommePression > 8){
    return true;
  }else{
    return false;
  }
 
}
