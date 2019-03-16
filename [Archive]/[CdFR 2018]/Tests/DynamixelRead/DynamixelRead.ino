#include <DynamixelSerial2.h> // rx 17 et TX 16

void setup(){
  Serial.begin(9600);
Dynamixel.begin(1000000,10);  // Initialize the servo at 1Mbps and Pin Control 2
}

void loop(){
  Serial.print("1: ");
  Serial.print(Dynamixel.readPosition(1));
  Serial.print("\t2: ");
  Serial.print(Dynamixel.readPosition(2));
  Serial.print("\t3: ");
  Serial.println(Dynamixel.readPosition(3));
  
  delay(2000);
}
