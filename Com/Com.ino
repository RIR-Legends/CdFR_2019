int __rasp_msg;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.write('a');
  if (Serial.available() > 0) {
    __rasp_msg = Serial.read();
    Serial.println("Reponse : " + __rasp_msg)
  }
}
