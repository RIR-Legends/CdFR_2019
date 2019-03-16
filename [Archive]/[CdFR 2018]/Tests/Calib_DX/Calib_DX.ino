#include "DX.h"

Dynamixels DX;

void setup() {
  Serial.begin(9600);
  DX.Parking(); //Ranger le bras
}

void loop() {
  DX.Parking();
}
