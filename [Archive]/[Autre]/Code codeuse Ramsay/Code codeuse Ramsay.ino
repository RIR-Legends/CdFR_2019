////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//// Debogage                                                                       ////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////



#define _DEBUG true
bool COTE = true;  // vert == true  //  jaune == false



////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//// Bibliotheques                                                                  ////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////



#include <SoftwareSerial.h>
#include <SimpleTimer.h>
#include <DynamixelSerial3.h>



////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//// Variables globales                                                             ////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


SoftwareSerial MySerial(10,11);  // MySerial(RX, TX)
byte zero = 0;


////////////////////////////////////////////////////////////////////////////////////////
// Grandeurs physiques                                                                //
////////////////////////////////////////////////////////////////////////////////////////

const double degre = 1.91;


const double perimetre_codeuse = 10.97;       // en cm
const double distance_entre_codeuses = 22.0;  // en cm
const int ticks_par_tour = 2000;              // en tick
const double angle_droit = (distance_entre_codeuses*PI)/4;
long cible_ticks = 0;
int offset = 0;                               // en tick // resultat obtenu experimentalement
int vitesse_moteur_gauche = 10;
int vitesse_moteur_droite = 10;

double distance_gauche;  // distance parcourue par la codeuse gauche
double distance_droite;  // distance parcourue par la codeuse droite

double consigne = 0;

int etape = 0;

int temps_bac = 5000;  // en ms

bool lent = false;


////////////////////////////////////////////////////////////////////////////////////////
// Definition des entrees                                                             //
////////////////////////////////////////////////////////////////////////////////////////


// Roue codeuse a gauche
const int codeuse_gauche_A = 19;  // (pin 19)
const int codeuse_gauche_B = 20;  // (pin 20)

// Roue codeuse a droite
const int codeuse_droite_A = 3;  // (pin 3)
const int codeuse_droite_B = 2;  // (pin 2)

const int tirette_input = A14;
const int tirette_output = A15;

const int tirette_switch_input = A8;
const int tirette_switch_output = A9;


////////////////////////////////////////////////////////////////////////////////////////
// Variables pour l echantillonnage                                                   //
////////////////////////////////////////////////////////////////////////////////////////


// Timer 1
SimpleTimer timer1;

// Initialisation des variables
const int frequence_echantillonnage = 50; // en Hz
const int periode_echantillonnage = 1000/frequence_echantillonnage; // en ms


////////////////////////////////////////////////////////////////////////////////////////
// Variables pour les compteurs                                                       //
////////////////////////////////////////////////////////////////////////////////////////


// Initialisation du compteur pour la codeuse a gauche
long position_codeuse_gauche = 0;  // position de depart = 0
bool A_gauche_set = false;
bool B_gauche_set = false;

// Initialisation du compteur pour la codeuse a droite
long position_codeuse_droite = 0;  // position de depart = 0
bool A_droite_set = false;
bool B_droite_set = false;


////////////////////////////////////////////////////////////////////////////////////////
// Variables pour le calcul du PID                                                    //
////////////////////////////////////////////////////////////////////////////////////////


// Initialisation des variables pour l asservissement du moteur a gauche
long erreur_gauche = 0;
double erreur_gauche_precedente = 0;
double somme_erreur_gauche = 0;

const double kp_gauche = 2.7;  // Coefficient proportionnel
const double ki_gauche = 0;  // Coefficient integrateur
const double kd_gauche = 0;  // Coefficient derivateur

// Initialisation des variables pour l asservissement du moteur a droite
long erreur_droite = 0;
double erreur_droite_precedente = 0;
double somme_erreur_droite = 0;

const double kp_droite = 2.0;  // Coefficient proportionnel
const double ki_droite = 0;  // Coefficient integrateur
const double kd_droite = 0;  // Coefficient derivateur

////////////////////////////////////////////////////////////////////////////////////////
// Autres variables                                                                   //
////////////////////////////////////////////////////////////////////////////////////////

bool t_gauche = false;
bool t_droite = false;
bool recule = false;

////////////////////////////////////////////////////////////////////////////////////////
// Variables caractéristiques du robot                                                //
////////////////////////////////////////////////////////////////////////////////////////

double x_actuel = 0;
double y_actuel = 0;

int angle_actuel = 0;

const int capteur_analogIn_AVD = 1;
const int capteur_analogIn_AVG = 0;

bool ActiveCapteurDroit = true;
bool ActiveCapteurGauche = true;

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//// Setup                                                                          ////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////



void setup()
{
  Serial.begin(115200);   // Initialisation de la communication avec la codeuse a droite
  Serial1.begin(115200);  // Initialisation de la communication avec la codeuse a gauche
  // baud rate = 115200 ==> connection plus rapide 
 
  Serial2.begin(38400);  
  // Initialisation de la communication avec la carte moteur
  MySerial.begin(9600);   // Initialisation de la communication avec la carte moteur (tour)
  
  Dynamixel.begin (1000000, 1);  // Initialisation de la communication avec les servos
  
  // Sorties codeuse a gauche
  pinMode(codeuse_gauche_A, INPUT);
  pinMode(codeuse_gauche_B, INPUT); 
  digitalWrite(codeuse_gauche_A, HIGH);  // Resistance interne arduino ON
  digitalWrite(codeuse_gauche_B, HIGH);  // Resistance interne arduino ON
  
  // Sorties codeuse a droite
  pinMode(codeuse_droite_A, INPUT);
  pinMode(codeuse_droite_B, INPUT); 
  digitalWrite(codeuse_droite_A, HIGH);  // Resistance interne arduino ON
  digitalWrite(codeuse_droite_B, HIGH);  // Resistance interne arduino ON
  
  pinMode(tirette_input, INPUT);
  pinMode(tirette_output, OUTPUT);
  
  // Interruption de la voie A de la codeuse a gauche en sortie 4 (pin 19)
  attachInterrupt(4, compteur_gauche_A, CHANGE);
  // Interruption de la voie B de la codeuse a gauche en sortie 3 (pin 20)
  attachInterrupt(3, compteur_gauche_B, CHANGE);
  
  // Interruption de la voie A de la codeuse a gauche en sortie 0 (pin 2)
  attachInterrupt(0, compteur_droite_A, CHANGE);
  // Interruption de la voie B de la codeuse a gauche en sortie 1 (pin 3)
  attachInterrupt(1, compteur_droite_B, CHANGE);
  
  Serial1.write(0);  // arreter les moteurs
  MySerial.write(zero); // arreter le moteur de la tour
  //Dynamixel.moveSpeed(5, 200, 300);  // ranger bras 
  Dynamixel.moveSpeed(5, 650, 500);  // mettre le bras (clap droite) a 0°
  Dynamixel.moveSpeed(2, 550, 500);  // mettre le bras (devant) a l horizontale
  Dynamixel.moveSpeed(4, 1000, 500);  // mettre le bac en position initiale
  delay(1000);  // Pause de 1 sec pour laisser le temps au moteur de s arreter si 
                // celui-ci est en marche
  
  // Echantillonage pour calcul du PID et asservissement
  // Toutes les 20ms, on recommence la routine  
  timer1.setInterval(periode_echantillonnage, repeter);
}



////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//// Loop                                                                           ////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////



void loop()
{
  analogWrite(tirette_switch_output, 255);
  analogWrite(tirette_output, 255);
  if(analogRead(tirette_switch_input)==1023)
  {
    COTE = false;
  }
  else
  {
    COTE = true;
  }
  delay(10);

  if(analogRead(tirette_input)==1023)
  {
    
  }
  else
  {
    delay(500);
    timer1.run();
  }
}



////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//// Fonctions                                                                      ////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////
// Compteurs                                                                          //
////////////////////////////////////////////////////////////////////////////////////////


// Interruption appelee a tous les changements d etat de la voie A de la codeuse a 
// gauche
void compteur_gauche_A()
{
  A_gauche_set = digitalRead(codeuse_gauche_A) == HIGH;
  
  if (t_gauche || recule)
  {
    // Modifie le compteur selon les deux etats de la codeuse a gauche
    position_codeuse_gauche += (A_gauche_set == B_gauche_set) ? -1 : +1;
  }
  else
  {
    position_codeuse_gauche += (A_gauche_set != B_gauche_set) ? -1 : +1;
  }
}

// Interruption appelee a tous les changements d etat de la voie B de la codeuse a 
// gauche
void compteur_gauche_B()
{
  B_gauche_set = digitalRead(codeuse_gauche_B) == HIGH;

  if (t_gauche || recule)
  {
    // Modifie le compteur selon les deux etats de la codeuse a gauche
    position_codeuse_gauche += (A_gauche_set != B_gauche_set) ? -1 : +1;
  }
  else
  {
    position_codeuse_gauche += (A_gauche_set == B_gauche_set) ? -1 : +1;
  } 
}

// Interruption appelee a tous les changements d etat de la voie A de la codeuse a 
// droite
void compteur_droite_A()
{
  A_droite_set = digitalRead(codeuse_droite_A) == HIGH;
  
  if (t_droite || recule)
  {
    // Modifie le compteur selon les deux etats de la codeuse a gauche
    position_codeuse_droite += (A_droite_set == B_droite_set) ? -1 : +1;
  }
  else
  {
    position_codeuse_droite += (A_droite_set != B_droite_set) ? -1 : +1;
  }
}

// Interruption appelee a tous les changements d etat de la voie B de la codeuse a 
// droite
void compteur_droite_B()
{
  B_droite_set = digitalRead(codeuse_droite_B) == HIGH;

  if (t_droite || recule)
  {
    // Modifie le compteur selon les deux etats de la codeuse a gauche
    position_codeuse_droite += (A_droite_set != B_droite_set) ? -1 : +1;
  }
  else
  {
    position_codeuse_droite += (A_droite_set == B_droite_set) ? -1 : +1;
  }
}


////////////////////////////////////////////////////////////////////////////////////////
// Controle les moteurs                                                                   //
////////////////////////////////////////////////////////////////////////////////////////

//Fonction appelée pour contrôler les moteurs
void tourner_moteurs(int MG, int MD)
{
  if(recule)
  {
    Serial2.write(192-MD-2);
    Serial2.write(64-MG);
  }
  else if(t_gauche)
  {
    Serial2.write(192+MD);
    Serial2.write(64-MG);
  }
  else if(t_droite)
  {
    Serial2.write(192-MD);
    Serial2.write(64+MG);
  }
  else
  {
    if(lent)
    {
      Serial2.write(192+MD-5);
      Serial2.write(64+MG-5);
    }
    else
    {
      Serial2.write(192+MD);
      Serial2.write(64+MG);
    }
  }
}

void monter_pied()
{
  MySerial.write(64-20);
  delay(5000);
  MySerial.write(zero);
}


////////////////////////////////////////////////////////////////////////////////////////
// Asservissement                                                                     //
////////////////////////////////////////////////////////////////////////////////////////


void asservissement()  // consigne en cm
{
  // Plus simple d asservir en ticks car ce sera toujours un nombre entier
  cible_ticks = ticks_par_tour*(consigne/perimetre_codeuse)-offset;
  
  // Calcul des erreurs
  erreur_gauche = cible_ticks - position_codeuse_gauche;
  somme_erreur_gauche += erreur_gauche;
  
  erreur_droite = cible_ticks - position_codeuse_droite;
  somme_erreur_droite += erreur_droite;
  
  // Calcul de la vitesse courante des moteurs
  vitesse_moteur_gauche = kp_gauche * erreur_gauche + kd_gauche * (erreur_gauche - erreur_gauche_precedente) + ki_gauche * (somme_erreur_gauche);
  vitesse_moteur_droite = kp_droite * erreur_droite + kd_droite * (erreur_droite - erreur_droite_precedente) + ki_droite * (somme_erreur_droite);

  // Ecrase l erreur precedente par la nouvelle erreur
  erreur_gauche_precedente = erreur_gauche;
  erreur_droite_precedente = erreur_droite;
  
  // Normalisation et controle de la vitesse du moteur a gauche
  if(vitesse_moteur_gauche > 10)
  {
    if(lent)
    {
      vitesse_moteur_gauche = 5;
    }
    else
    {
      vitesse_moteur_gauche = 10;
    }
  }
  else if(vitesse_moteur_gauche < 0) 
  {
    vitesse_moteur_gauche = 0;
  }
  
  // Normalisation et controle de la vitesse du moteur a droite
  if(vitesse_moteur_droite > 10)
  {
    if(lent)
    {
      vitesse_moteur_droite = 5;
    }
    else
    {
      vitesse_moteur_droite = 10;
    }
  }
  else if(vitesse_moteur_droite < 0) 
  {
    vitesse_moteur_droite = 0;
  }
      
  tourner_moteurs(vitesse_moteur_gauche, vitesse_moteur_droite);
  
  distance_gauche = ((double)position_codeuse_gauche/(double)ticks_par_tour)*(double)perimetre_codeuse;
  distance_droite = ((double)position_codeuse_droite/(double)ticks_par_tour)*(double)perimetre_codeuse;
  
  // Utile pour les graphes sur excel
  if(_DEBUG)
  {
    static unsigned long temps;
    
    temps = millis();  // Renvoie le nombre de millisecondes depuis que la carte Arduino 
                       // a commence a executer le programme
    
    Serial.print(temps);
    Serial.print("\t \t");
    
    // Affiche sur le moniteur les donnees concernant le moteur a gauche
    Serial.print(erreur_gauche);
    Serial.print("\t");
    Serial.print(position_codeuse_gauche);
    Serial.print("\t");
    Serial.print(distance_gauche);
    Serial.print("\t");
    Serial.print(vitesse_moteur_gauche);
    Serial.print("\t \t");
    
    // Affiche sur le moniteur les donnees concernant le moteur a droite
    Serial.print(erreur_droite);
    Serial.print("\t");
    Serial.print(position_codeuse_droite);
    Serial.print("\t");
    Serial.print(distance_droite);
    Serial.print("\t");
    Serial.print(vitesse_moteur_droite);
    Serial.print("\t \t");
    // Serial.println(etape);
    
    // Affiche sur le moniteur la position et l angle actuels du robot
    Serial.print(x_actuel);
    Serial.print("\t");
    Serial.print(y_actuel);
    Serial.print("\t");
    Serial.print(consigne);
    Serial.print("\t");
    Serial.println(angle_actuel);
  }
}

void incremente_coordonees()
{
  switch(angle_actuel)
  {
    case 0 :
      if(recule)
      {
        x_actuel -= (distance_gauche + distance_droite) / 2;
      }
      else
      {
        x_actuel += (distance_gauche + distance_droite) / 2;
      }
    break;
    
    case 90 :
      if(recule)
      {
        y_actuel -= (distance_gauche + distance_droite) / 2;
      }
      else
      {
        y_actuel += (distance_gauche + distance_droite) / 2;
      }
    break;
    
    case 180 :
      if(recule)
      {
        x_actuel += (distance_gauche + distance_droite) / 2;
      }
      else
      {
        x_actuel -= (distance_gauche + distance_droite) / 2;
      }
    break;
    
    case 270 :
      if(recule)
      {
        y_actuel += (distance_gauche + distance_droite) / 2;
      }
      else
      {
        y_actuel -= (distance_gauche + distance_droite) / 2;
      }
    break;
  }
}

void avance()
{
  do
  {
    while ((vitesse_moteur_gauche != 0 || vitesse_moteur_droite != 0) && !(Detection(capteur_analogIn_AVD, 18.5) && ActiveCapteurDroit) && !(Detection(capteur_analogIn_AVG, 17) && ActiveCapteurGauche))
    {
      asservissement();
    }
    Serial2.write(0);
  } while (vitesse_moteur_gauche != 0 || vitesse_moteur_droite != 0);
  remise_zero();
  etape++;
}

boolean Detection(const int broche_analogIN_capteur, int distance)
{
  int recup1;
  float recup_moment2;
  float recup_moment1;
  float traitement_capteur;
  
  recup1 = analogRead(broche_analogIN_capteur);
  if(recup1 != 0)
  {
    recup_moment1 = 13.75/(float(recup1)*0.004883);
  }
  else
  {
    recup_moment1 = 10000;
  }
  
  recup1 = analogRead(broche_analogIN_capteur);
  if(recup1 != 0)
  {
    recup_moment2 = 13.75/(float(recup1)*0.004883);
  }
  else
  {
    recup_moment2 = 10000;
  }
  
  traitement_capteur = (recup_moment1 + recup_moment2)/2.0;
  
  if(traitement_capteur < distance) 
  {
    return true;
  }
  else
  {
    return false;
  }
  
}

void reculer()
{
  recule = true;
  do
  {
    asservissement();
  } while (vitesse_moteur_gauche != 0 || vitesse_moteur_droite != 0);
  remise_zero();
  etape++;
  recule = false;
}

void tourner_droite()
{
  t_droite = true;
  do
  {
    asservissement();
  } while (vitesse_moteur_gauche != 0 || vitesse_moteur_droite != 0);
  angle_actuel -= 90 % 360;
  remise_zero();
  etape++;
  t_droite = false;
}

void tourner_gauche()
{
  t_gauche = true;
  do
  {
    asservissement();
  } while (vitesse_moteur_gauche != 0 || vitesse_moteur_droite != 0);
  angle_actuel += 90 % 360;
  remise_zero();
  etape++;
  t_gauche = false;
}

void stop_moteurs()
{
  Serial2.write(0);
  delay(500);
}

void arret_total()
{
  while(1) Serial2.write(0);
}

void remise_zero()
{
  position_codeuse_gauche = 0;
  position_codeuse_droite = 0;
  distance_gauche = 0;
  distance_droite = 0;
  vitesse_moteur_gauche = 10;  
  vitesse_moteur_droite = 10;
}

void ouvrir_tour_bas()
{
  Dynamixel.moveSpeed(2, 175, 500);  // ouvrir tour (partie du bas)
}

void fermer_tour_bas()
{
  Dynamixel.moveSpeed(2, 480, 500);  // fermer tour (partie du bas)
}

void ouvrir_tour_haut()
{
  Dynamixel.moveSpeed(3, 465, 500);  // ouvrir tour (partie du haut)
}

void fermer_tour_haut()
{
  Dynamixel.moveSpeed(3, 165, 500);  // fermer tour (partie du haut)
}

void bac()
{
  static int temps_bac_debut = millis();
  while(millis() < (temps_bac_debut + temps_bac))
  {
    // je suppose que le dynamixel est "entre" les distributeurs
    Dynamixel.moveSpeed(5, 600, 500);
    delay(500);
    // Dynamixel.moveSpeed(5, 550, 300);  // si le bac est a gauche
    //Dynamixel.moveSpeed(5, 425, 500);  // si le bac est a droite
    //delay(500);
  }
  Dynamixel.moveSpeed(5, 200, 300);
  delay(500);
}

void ouvrir_bac()
{
  Dynamixel.moveSpeed(1, 610, 50);
  delay(5000);
}


void fermer_bac()
{
  Dynamixel.moveSpeed(1, 500, 50);
  delay(1000);
}


//position initiale 650
//90 380
//180 0

void fermer_clap()
{
  Dynamixel.moveSpeed(5, 380, 500);
  delay(500);
}

void eviter_clap_plus()
{
  Dynamixel.moveSpeed(5, 0, 500);
  delay(500);
}

void eviter_clap()
{
  Dynamixel.moveSpeed(5, 650, 500);
  delay(500);
}

void recuperer_gobelet_arriere()
{
  Dynamixel.moveSpeed(4, 375, 500);
  delay(500);
}

void eviter_gobelet_arriere()
{
  Dynamixel.moveSpeed(4, 800, 500);
  delay(500);
}

void recuperer_gobelet_devant()
{
  Dynamixel.moveSpeed(2, 300, 500);
  delay(500);
}

void eviter_gobelet_devant()
{
  Dynamixel.moveSpeed(2, 550, 500);
  delay(500);
}

void repeter()
{
  if(COTE)
  {
    
    // cote vert
    
    
    
     // code pour les pieds
    
    consigne = 40.0;
    avance(); 
    consigne = 40.0;
    avance();
    
    stop_moteurs();
    
    consigne = angle_droit;
    tourner_gauche();
    stop_moteurs();
    
    consigne = 28.0;
    avance();
    consigne = 27.0;
    avance();
    stop_moteurs();
    
    consigne = angle_droit+degre;
    tourner_gauche();
    stop_moteurs();
    
    consigne = 25.0;
    avance();
    consigne = 15.0;
    avance();
    stop_moteurs();
    
    consigne = angle_droit+degre;
    tourner_gauche();
    stop_moteurs();
    
    consigne = 33.0;
    avance();
    consigne = 35.0;
    avance();
    stop_moteurs();
    
    consigne = angle_droit+0.6;
    tourner_droite();
    stop_moteurs();
    remise_zero();
    delay(1);
    
    consigne = 30.0;
    avance();
    stop_moteurs();
    
    // claps
    
    consigne = 20;
    reculer();
    stop_moteurs();
    
    remise_zero();
    consigne = angle_droit-degre;
    tourner_droite();
    stop_moteurs();
    remise_zero();
    delay(1);
    
    consigne = 40;
    avance();
    ActiveCapteurDroit = false;
    ActiveCapteurGauche = false;
    consigne = 38;
    avance();
    ActiveCapteurDroit = true;
    ActiveCapteurGauche = true;
    stop_moteurs();
    remise_zero();
    delay(1);
    
    consigne = angle_droit+degre;
    tourner_gauche();
    stop_moteurs();    
    
    fermer_clap();
    
    consigne = 5;
    reculer();
    
    eviter_clap_plus();
    eviter_clap();
    
    consigne = 20;
    avance();
    consigne = 18;
    avance();
    lent == true;
    consigne = 16.5;
    avance();
    stop_moteurs();
    recuperer_gobelet_devant();
    stop_moteurs();
    consigne = 8;
    avance();
    
    eviter_clap_plus();
    
    // gobelets
    
    lent == false;
    
    consigne = 0.1;
    tourner_droite();
    
    consigne = 20;
    reculer();
    reculer();
    reculer();
    stop_moteurs();
    
    consigne = angle_droit;
    tourner_gauche();
    
    consigne = 20;
    avance();
    avance();
    avance();
    
    consigne = angle_droit;
    tourner_droite();
    
    consigne = 20;
    avance();
    avance();
    
    eviter_gobelet_devant();
    
    consigne = 5;
    reculer();
    
    arret_total();
  }
  
  
  
  else
  
  
  
  
  {
    
    
    //cote jaune
    
    // code pour les pieds
    
    consigne = 40.0;
    avance(); 
    consigne = 40.0;
    avance();
    
    stop_moteurs();
    
    consigne = angle_droit-1.9;
    tourner_droite();
    stop_moteurs();
    
    consigne = 27.0;
    avance();
    consigne = 27.0;
    avance();
    stop_moteurs();
    
    consigne = angle_droit;
    tourner_droite();
    stop_moteurs();
    
    consigne = 30.0;
    avance();
    consigne = 15.0;
    avance();
    stop_moteurs();
    
    consigne = angle_droit+0.3;
    tourner_droite();
    stop_moteurs();
    
    consigne = 30.0;
    avance();
    consigne = 35.0;
    avance();
    stop_moteurs();
    
    consigne = angle_droit+degre;
    tourner_gauche();
    stop_moteurs();
    remise_zero();
    delay(1);
    
    consigne = 20.0;
    avance();
    stop_moteurs();
    
    // claps
    
    consigne = 30;
    reculer();
    stop_moteurs();
    
    remise_zero();
    consigne = angle_droit+0.5;
    tourner_gauche();
    stop_moteurs();
    remise_zero();
    delay(1);
    
    consigne = 37;
    avance();
    ActiveCapteurDroit = false;
    ActiveCapteurGauche = false;
    consigne = 38;
    avance();
    ActiveCapteurDroit = true;
    ActiveCapteurGauche = true;
    stop_moteurs();
    remise_zero();
    delay(1);
    
    fermer_clap();
    consigne = angle_droit-0.5;
    tourner_gauche();
    consigne = 6;
    avance();
    stop_moteurs();
    eviter_clap();
    
    delay(500);
    
    remise_zero();
    eviter_clap_plus();
    consigne = 25;
    reculer();
    consigne = 23;
    reculer();
    consigne = 20;
    reculer();

    stop_moteurs();
    
    eviter_clap();
    recuperer_gobelet_arriere();
    stop_moteurs();
    consigne = 6;
    avance();
    
    // gobelets
    
    recuperer_gobelet_arriere();
    
    stop_moteurs();
    
    consigne=25;
    avance();
    avance();
    
    consigne=angle_droit;
    tourner_gauche();
    
    consigne=35;
    avance();
    avance();
    
    consigne=angle_droit;
    tourner_droite();
    
    consigne=20;
    reculer();
    
    eviter_gobelet_arriere();
    
    consigne = 6;
    avance();
    
    arret_total();
  }
}
