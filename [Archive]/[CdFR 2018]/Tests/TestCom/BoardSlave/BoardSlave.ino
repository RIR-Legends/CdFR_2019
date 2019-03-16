void setup(){
  Serial.begin(9600);
}

void loop(){
 
  DDRL = B11110000; //0 input et 1 output
  PORTL |= B00100000;
  byte Val = PINL & B00001111;
  Serial.println(Val == B00001110);
}

