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

    while(!RIR_checkAndRead()){
      delay(10);
    }
    // Do the action
    delay(5000);

    RIR_send(Action_Finished);

    while(!RIR_checkAndRead()){
      delay(10);
    }
    // Suppose to turn off robot.
}

void RIR_send(int msg)
{
    __ard_msg = msg;
    while (__rasp_msg != Recu){
        Serial.write(__ard_msg);
        delay(100);
        if (Serial.available() > 0) {
          __rasp_msg = Serial.read();
        }
    }
    __ard_msg = Attente;
    for (int i = 0 ; i < 30 ; i++){
        Serial.write(__ard_msg);
        delay(10);
    }
    Serial.println("Message sent");
}

void RIR_read()
{
    while (Serial.available() && (__rasp_msg == Attente || __rasp_msg == Recu)){
        __rasp_msg = Serial.read();
    }
    // Interprete value, so change internal variables
    
    __ard_msg = Recu;
    while (Serial.available() && (Serial.read() != Attente || Serial.read() != Recu)){
        Serial.write(__ard_msg);
    }
}

bool RIR_check()
{
    Serial.write(Attente);
    return Serial.read() != Attente && Serial.read() != Recu;
    return false;
}

bool RIR_checkAndRead()
{
    if (RIR_check()){
        RIR_read();
        return true;
    }
    return false;
}
