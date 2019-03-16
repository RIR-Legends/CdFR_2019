#include "DX.h"

//Au Dieu Marsoux

Dynamixels::Dynamixels()
{
  Dynamixel.begin(1000000,PINDX);
}

void Dynamixels::Parking()
{
  Dynamixel.setMaxTorque(3,1023);
  Dynamixel.moveSpeed(3,350,600);
  Dynamixel.setMaxTorque(2,1023);
  Dynamixel.moveSpeed(2,900,200);
  delay(400);
  Dynamixel.setPunch(1,1023); //limite du courant (0-1023)
  Dynamixel.setMaxTorque(1,1023); 
  Dynamixel.moveSpeed(1,700,500); 
  
  delay(1000);
}

void Dynamixels::SortieBras()
{
  //sortie du bras
  Dynamixel.setPunch(1,80); //limite du courant (0-1023)
  Dynamixel.moveSpeed(1,330,200);
  delay(600);
  Dynamixel.moveSpeed(2,360,500);  
  delay(1000);
}

void Dynamixels::DescenteMain()
{
   Dynamixel.setPunch(1,10); //limite du courant (0-1023)
  Dynamixel.moveSpeed(1,360,200);
  delay(500);
  Dynamixel.moveSpeed(2,360,500);
  delay(1000);
}

void Dynamixels::RemonteMain()
{
  Dynamixel.setPunch(1,80); //limite du courant (0-1023)
  Dynamixel.moveSpeed(1,300,200);
  delay(1000);
  Dynamixel.moveSpeed(2,850,200);
  delay(1000);
  Dynamixel.moveSpeed(1,500,100);
  delay(200);
}

void Dynamixels::Turn90()
{
  Dynamixel.moveSpeed(3,346,600);
  delay(1000);
}
