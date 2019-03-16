void setup(){
  Serial.begin(9600);
}

void loop(){
 
  DDRL = B00001111; //0 input et 1 output
  PORTL |= B00001100;
  byte Val = PINL & B11110000;
  Serial.println(Val == B01100000);
}

