#include <DynamixelSerial2.h> // rx 17 et TX 16

void setup(){
Dynamixel.begin(1000000,10);  // Initialize the servo at 1Mbps and Pin Control 2
delay(1000);
 
Dynamixel.ledStatus(1,OFF);
delay(1000);
Dynamixel.ledStatus(1,ON);
Dynamixel.ledStatus(2,OFF);
delay(1000);
Dynamixel.ledStatus(2,ON);
Dynamixel.ledStatus(3,OFF);
delay(1000);
Dynamixel.ledStatus(3,ON);

}

void loop(){
  
  // position parking 600,900,360
  Dynamixel.setMaxTorque(3,1023);
  Dynamixel.moveSpeed(3,360,600);
  Dynamixel.setMaxTorque(2,1023);
  Dynamixel.moveSpeed(2,900,200);
  delay(400);
  Dynamixel.setPunch(1,1023); //limite du courant (0-1023)
  Dynamixel.setMaxTorque(1,1023); 
  Dynamixel.moveSpeed(1,600,200); 
  delay(5000);  
  
  delay(500);

  //sortie du bras
  Dynamixel.setPunch(1,80); //limite du courant (0-1023)
  Dynamixel.moveSpeed(1,330,200);
  delay(1000);
  Dynamixel.moveSpeed(2,360,500);
  delay(6000);
  Dynamixel.setPunch(1,10); //limite du courant (0-1023)
  Dynamixel.moveSpeed(1,360,200);
  delay(2000);
  Dynamixel.moveSpeed(2,360,500);
  delay(3000);

  //
  //ASSpiration des cubes
  //
  
  // levée des cubes
  Dynamixel.setPunch(1,80); //limite du courant (0-1023)
  Dynamixel.moveSpeed(1,300,200);
  delay(1000);
  Dynamixel.moveSpeed(2,800,200);
  delay(1000);
  Dynamixel.moveSpeed(1,500,100);
  delay(200);
  Dynamixel.moveSpeed(2,830,500);
  delay(200);
  /*Dynamixel.moveSpeed(3,800,600);
  delay(200);
  Dynamixel.moveSpeed(3,0,600);*/
  delay(1000);
  
  Dynamixel.setVoltageLimit(3,65,160);  // Set Operating Voltage from 6.5v to 26v
         // 50% of Torque
  Dynamixel.setSRL(3,2);                // Set the SRL to Return All

  Dynamixel.ledStatus(3,ON);           // Turn ON the LED
  
  delay(1000);
  
}
