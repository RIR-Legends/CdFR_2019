//Capteurs IR
#define CAPT_AVG A6
#define CAPT_ARD A5
#define CAPT_AVD A4
#define CAPT_ARG A7

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //while(analogRead(CAPT_AVG) > 140) { qik.setBrakes(127,127); Serial.println("AVG");}
  //while(analogRead(CAPT_AVD) > 140) { qik.setBrakes(127,127); Serial.println("AVD");}

  Serial.print(analogRead(CAPT_AVG));
  Serial.print("\t");
  Serial.println(analogRead(CAPT_AVD));
  Serial.print(analogRead(CAPT_ARG));
  Serial.print("\t");
  Serial.println(analogRead(CAPT_ARD));
  Serial.println();

  delay(500);
}
