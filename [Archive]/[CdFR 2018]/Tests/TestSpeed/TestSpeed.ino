#include <SoftwareSerial.h>
#include <PololuQik.h>

PololuQik2s12v10 qik(7,8,9);
int Speed = 14;

void setup() {
  qik.init();
}

void loop() {
  qik.setSpeeds(-Speed, Speed); //Vitesse min
}

