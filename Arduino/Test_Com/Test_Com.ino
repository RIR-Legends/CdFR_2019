// In and Out
int Recu            = '1';
int Attente         = '0';
int Action_Finished = 't';
    
// In
int Arret           = 'A';
int Initialisation  = 'I';
int Transport       = 'T';
int Palet_Floor_In  = 'f';
int Palet_Wall_In   = 'w';
int Palet_Floor_Out = 'F';
int Palet_Wall_Out  = 'W';

// Out
int Tirette         = 'D';
int Violet          = 'v';
int Orange          = 'o';

int Avance          = 'a';
int Recule          = 'r';
    
int __ard_msg = Attente;
int __rasp_msg = Attente;

void setup() {
  Serial.begin(9600);  
}


void loop() {
    // Sending side
    RIR_send(Orange);

    RIR_send(Tirette);

    while(!RIR_read()){
      continue;
    }
    // Do the action

    RIR_send(Action_Finished);

    while(!RIR_read()){
      continue;
    }
    // Suppose to turn off robot.
    delay(100000);
}

void RIR_send(int msg)
{
    __ard_msg = msg;
    while (__rasp_msg != Recu){
        Serial.write(__ard_msg);
        Serial.flush();  
        if (Serial.available() > 0) {
          __rasp_msg = Serial.read();
        }
        delay(100);
    }
    
    Serial.write(__ard_msg);
    delay(100);
}

bool RIR_read()
{
    Serial.flush();  
    if (Serial.available() > 0) {
      __rasp_msg = Serial.read();
    }
    if (__rasp_msg == Attente || __rasp_msg == Recu){
      delay(100);
      return false;
    }
    // Interprete value
    
    __ard_msg = Recu;
    Serial.write(__ard_msg);
    delay(100);
    return true;
}


