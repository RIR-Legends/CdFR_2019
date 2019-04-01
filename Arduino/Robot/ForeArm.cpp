#include "ForeArm.h"

ForeArm::ForeArm(){
  Dynamixel.begin(1000000,15);  // Inicialize the servo at 1Mbps and Pin Control 2
}

void ForeArm::MoveTo(double pDX1, double pDX2, double vDX1, double vDX2){
	Dynamixel.moveSpeed(1, pDX1,vDX1);
  Dynamixel.moveSpeed(2, pDX2, vDX2);
}
