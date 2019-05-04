#include "Foo.h"

void setup() {
  // put your setup code here, to run once:
  Foo::Setup();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(Foo::Return_Compteur());
}
