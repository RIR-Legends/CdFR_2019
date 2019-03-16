#define P1 29
#define P2 31
#define P3 33
#define P4 35
#define P5 37

void setup(){
  Serial.begin(9600);
  pinMode(P1,OUTPUT);
  pinMode(P2,OUTPUT);
  pinMode(P3,OUTPUT);
  pinMode(P4,OUTPUT);
  pinMode(P5,OUTPUT);
}

void loop(){
  Serial.println("1");
  digitalWrite(P5,LOW);
  digitalWrite(P1,HIGH);
  delay(1000);
  Serial.println("2");
  digitalWrite(P1,LOW);
  digitalWrite(P2,HIGH);
  delay(1000);
  Serial.println("3");
  digitalWrite(P2,LOW);
  digitalWrite(P3,HIGH);
  delay(1000);
  Serial.println("4");
  digitalWrite(P3,LOW);
  digitalWrite(P4,HIGH);
  delay(1000);
  Serial.println("5");
  digitalWrite(P4,LOW);
  digitalWrite(P5,HIGH);
  delay(1000);
}

