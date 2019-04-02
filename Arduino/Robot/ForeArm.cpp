#include "ForeArm.h"

ForeArm::ForeArm(){
  Dynamixel.begin(1000000,15);  // Inicialize the servo at 1Mbps and Pin Control 2
}

void ForeArm::MoveTo(double pDX1, double pDX2){
	Dynamixel.move(1, pDX1);
  Dynamixel.move(2, pDX2);
}
