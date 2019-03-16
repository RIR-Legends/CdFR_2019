#include "digitalWriteFast.h"
#include "SimpleTimer.h"
#include "SoftwareSerial.h"
#include "PololuQik.h"
#include "Wire.h" 
#include "DynamixelSerial2.h"

struct point
{
  float X;
  float Y;
  
  float Theta_rotation;
  int choix_fonction;
  bool av_droit_IR;
  bool av_gauche_IR;
  bool ar_droit_IR;
  bool ar_gauche_IR;
  bool ar_centre_IR;
};
point pos[30];

PololuQik2s12v10 qik(4, 5, 6);
SimpleTimer timer1;  // def timer de l'echantillonage

/*********************** Constante du robot ************************************
  Diametre des roues = 5.08 cm
  Perimetre des roues = PI*5.08
  Nombre de ticks par tour => 2400 - 2420
********************************************************************************/

float ecart_roue= 27; // distance entre les deux roues en 13 cm<- valeur theorique
float freqEch = 1;
float tickParTour = 2000;
float tick_cm = (7.15 * PI) / tickParTour;
float coeff_Etalonnage_Position = 1.0804; // permet de reajuster la pos therorique avec la reelle
float degreePerRad = 57.295779513;

/*********************** Position du robot *************************************
  Position en cooRonnees cartesiennes X et Y a t, qui seront stocke dans dX et
  dY lors du calcul de la position suivante
  dist_R et L est la distance parcouru par chaque roue en cm
  Theta_ini est l'angle de depart, Theta est l'angle du robot a t et dTheta est
  l'angle du robot par rapport a la derniere position
  ticks_R et G est le nombre de ticks releve pour chaque roues a t
********************************************************************************/

float X = -87;
float Y = 24;
float X0 = -87;
float Y0 = 24;
float dX = 0, dY = 0;
float dist_R = 0, dist_L = 0;
float dist, d_dist = 0, dist_pre = 0;

/*********************** Variable de l'angle Theta ***************************/

float Theta = 0, dTheta, Theta_pre, Theta_moy, Theta_moy_rad, dTheta_rad,Theta_rotation;
float Theta_ini= 0,Theta_direction,orientation,dDirection,consigne_dist,s;

/************************ Commande Robot *************************************/

float commande_R,commande_L;

/*********************** Régulation P ***************************************/

float regulation_vitesse,angle_R,angle_L;
float Kp_R=1,Kp_angle_R=1;
float Kp_L=1,Kp_angle_L=1;
int etape = 0,choix_fonction;

/*********************** Tickencodeur **************************************/

long ticks_R = 0;
long ticks_L = 0;

#define VOIXA_DROITE 18 // Fil GRIS du codeur
#define VOIXB_DROITE 19 // Fil VERT du codeur

/************ Cablage des vecteurs d'interruptions pour le codeur droit *******/

#define vectInterruptA_droit 5 // Va avec VOIXA_DROIT
#define vectInterruptB_droit 4 // Va avec VOIXB_DROIT


#define VOIXA_GAUCHE 2 // Fil GRIS du codeur
#define VOIXB_GAUCHE 3 // Fil VERT du codeur

/**************Cablage des vecteurs d'interruptions pour le codeur gauche******/

#define vectInterruptA_gauche 0 // Va avec VOIXA_GAUCHE
#define vectInterruptB_gauche 1 // Va avec VOIXB_GAUCHE

void Repeat_Me()
{
 
}

void setup()
{    
  Serial.begin(9600);
 // Dynamixel2.begin(1000000);
  
  /*********************** Echantillonnage **************************************/

  /***************** Initialisation de la Qik **********************************/
  qik.init();

  /* Définition des pins en mode entrée et activation de la résistance de pull-up */
  
  // CODEUR DROIT
  pinMode(VOIXA_DROITE, INPUT);
  pinMode(VOIXB_DROITE, INPUT);
  digitalWrite(VOIXA_DROITE, HIGH);
  digitalWrite(VOIXB_DROITE, HIGH);
  // CODEUR GAUCHE
  pinMode(VOIXA_GAUCHE, INPUT);
  pinMode(VOIXB_GAUCHE, INPUT);
  digitalWrite(VOIXA_GAUCHE, HIGH);
  digitalWrite(VOIXB_GAUCHE, HIGH);

  /************** Attache le changement d'état de la PIN à une fonction ************/
  attachInterrupt(vectInterruptA_droit, GestionInterruptionCodeurPinA_DR, RISING);
  attachInterrupt(vectInterruptB_droit, GestionInterruptionCodeurPinB_DR, RISING);
  attachInterrupt(vectInterruptA_gauche, GestionInterruptionCodeurPinA_GA, RISING);
  attachInterrupt(vectInterruptB_gauche, GestionInterruptionCodeurPinB_GA, RISING);

  /********************** Initialisation des étapes ***************************/

analogWrite(A12,255);
if(analogRead(A13)==1023)
{
pos[0].X = -87;
pos[0].Y = 95;
pos[0].Theta_rotation = 0;
pos[0].choix_fonction = 1;
pos[0].av_droit_IR = false;
pos[0].av_gauche_IR = false;
pos[0].ar_droit_IR = false;
pos[0].ar_gauche_IR = false;
pos[0].ar_centre_IR = false;

pos[1].X = -87;
pos[1].Y = 52;
pos[1].Theta_rotation = 0;
pos[1].choix_fonction = 10;
pos[1].av_droit_IR = false;
pos[1].av_gauche_IR = false;
pos[1].ar_droit_IR = true;
pos[1].ar_gauche_IR = true;
pos[1].ar_centre_IR = true;

pos[2].X = -87;
pos[2].Y = 52;
pos[2].Theta_rotation = -90;
pos[2].choix_fonction = 2;
pos[2].av_droit_IR = false;
pos[2].av_gauche_IR = false;
pos[2].ar_droit_IR = true;
pos[2].ar_gauche_IR = true;
pos[2].ar_centre_IR  = true;

pos[3].X = -168;
pos[3].Y =52;
pos[3].Theta_rotation = -90;
pos[3].choix_fonction = 1;
pos[3].av_droit_IR = true;
pos[3].av_gauche_IR = true;
pos[3].ar_droit_IR = false;
pos[3].ar_gauche_IR = false;
pos[3].ar_centre_IR = false;

pos[4].X = -168;
pos[4].Y = 52;
pos[4].Theta_rotation = 0;
pos[4].choix_fonction = 2;
pos[4].av_droit_IR = true;
pos[4].av_gauche_IR = false;
pos[4].ar_droit_IR = false;
pos[4].ar_gauche_IR = false;
pos[4].ar_centre_IR = true;

pos[5].X = -170;
pos[5].Y = 92;
pos[5].Theta_rotation = 0;
pos[5].choix_fonction = 1;
pos[5].av_droit_IR = true;
pos[5].av_gauche_IR = false;
pos[5].ar_droit_IR = false;
pos[5].ar_gauche_IR = false;
pos[5].ar_centre_IR = true;

pos[6].X = -175;
pos[6].Y = 55;
pos[6].Theta_rotation = 0;
pos[6].choix_fonction = 10;
pos[6].av_droit_IR = true;
pos[6].av_gauche_IR = false;
pos[6].ar_droit_IR = false;
pos[6].ar_gauche_IR = false;
pos[6].ar_centre_IR = true;

pos[7].X = -175;
pos[7].Y = 55;
pos[7].Theta_rotation = 0;
pos[7].choix_fonction = 7;
pos[7].av_droit_IR = true;
pos[7].av_gauche_IR = false;
pos[7].ar_droit_IR = false;
pos[7].ar_gauche_IR = false;
pos[7].ar_centre_IR = true;

pos[8].X = -175;
pos[8].Y = 97;
pos[8].Theta_rotation = 0;
pos[8].choix_fonction = 1;
pos[8].av_droit_IR = true;
pos[8].av_gauche_IR = false;
pos[8].ar_droit_IR = false;
pos[8].ar_gauche_IR = false;
pos[8].ar_centre_IR = true;

pos[9].X = -175;
pos[9].Y = 55;
pos[9].Theta_rotation = 0;
pos[9].choix_fonction = 10;
pos[9].av_droit_IR = true;
pos[9].av_gauche_IR = false;
pos[9].ar_droit_IR = false;
pos[9].ar_gauche_IR = false;
pos[9].ar_centre_IR = true;

pos[10].X = -175;
pos[10].Y = 95;
pos[10].Theta_rotation = 0;
pos[10].choix_fonction = 1;
pos[10].av_droit_IR = true;
pos[10].av_gauche_IR = false;
pos[10].ar_droit_IR = false;
pos[10].ar_gauche_IR = false;
pos[10].ar_centre_IR = true;

pos[11].X = -175;
pos[11].Y = 95;
pos[11].Theta_rotation = 0;
pos[11].choix_fonction = 11;
pos[11].av_droit_IR = true;
pos[11].av_gauche_IR = false;
pos[11].ar_droit_IR = true;
pos[11].ar_gauche_IR = false;
pos[11].ar_centre_IR = true;


pos[12].X = -175;
pos[12].Y = 110;
pos[12].Theta_rotation = 0;
pos[12].choix_fonction = 1;
pos[12].av_droit_IR = true;
pos[12].av_gauche_IR = false;
pos[12].ar_droit_IR = false;
pos[12].ar_gauche_IR = false;
pos[12].ar_centre_IR = true;

pos[13].X = -175;
pos[13].Y = 110;
pos[13].Theta_rotation = 90;
pos[13].choix_fonction = 7;
pos[13].av_droit_IR = true;
pos[13].av_gauche_IR = false;
pos[13].ar_droit_IR = false;
pos[13].ar_gauche_IR = false;
pos[13].ar_centre_IR = true;

pos[14].X = -175;
pos[14].Y = 110;
pos[14].Theta_rotation = 90;
pos[14].choix_fonction = 2;
pos[14].av_droit_IR = true;
pos[14].av_gauche_IR = false;
pos[14].ar_droit_IR = false;
pos[14].ar_gauche_IR = false;
pos[14].ar_centre_IR = false;

pos[15].X = -175;
pos[15].Y = 160;
pos[15].Theta_rotation = 90;
pos[15].choix_fonction = 8;
pos[15].av_droit_IR = false;
pos[15].av_gauche_IR = false;
pos[15].ar_droit_IR = false;
pos[15].ar_gauche_IR = false;
pos[15].ar_centre_IR = false;

pos[16].X = -175;
pos[16].Y = 160;
pos[16].Theta_rotation = 180;
pos[16].choix_fonction = 2;
pos[16].av_droit_IR = false;
pos[16].av_gauche_IR = false;
pos[16].ar_droit_IR = false;
pos[16].ar_gauche_IR = false;
pos[16].ar_centre_IR = false;

pos[17].X = -165;
pos[17].Y = 52;
pos[17].Theta_rotation = 180;
pos[17].choix_fonction = 1;
pos[17].av_droit_IR = false;
pos[17].av_gauche_IR = false;
pos[17].ar_droit_IR = false;
pos[17].ar_gauche_IR = false;
pos[17].ar_centre_IR = false;

pos[18].X = -165;
pos[18].Y = 70;
pos[18].Theta_rotation = 90;
pos[18].choix_fonction = 2;
pos[18].av_droit_IR = false;
pos[18].av_gauche_IR = false;
pos[18].ar_droit_IR = false;
pos[18].ar_gauche_IR = false;
pos[18].ar_centre_IR = false;

pos[19].X = -57;
pos[19].Y = 70;
pos[19].Theta_rotation = 90;
pos[19].choix_fonction = 1;
pos[19].av_droit_IR = false;
pos[19].av_gauche_IR = false;
pos[19].ar_droit_IR = false;
pos[19].ar_gauche_IR = false;
pos[19].ar_centre_IR = false;

pos[20].X = -57;
pos[20].Y = 70;
pos[20].Theta_rotation = 0;
pos[20].choix_fonction = 2;
pos[20].av_droit_IR = false;
pos[20].av_gauche_IR = false;
pos[20].ar_droit_IR = false;
pos[20].ar_gauche_IR = false;
pos[20].ar_centre_IR = false;

//pos[21].X = -165;
//pos[21].Y = 110;
//pos[21].Theta_rotation = -90;
//pos[21].choix_fonction = 3;
//pos[21].av_droit_IR = false;
//pos[21].av_gauche_IR = false;
//pos[21].ar_droit_IR = false;
//pos[21].ar_gauche_IR = false;
//pos[21].ar_centre_IR = false;
//
//pos[22].X = -165;
//pos[22].Y = 110;
//pos[22].Theta_rotation = PI;
//pos[22].choix_fonction = 2;
//pos[22].av_droit_IR = false;
//pos[22].av_gauche_IR = false;
//pos[22].ar_droit_IR = false;
//pos[22].ar_gauche_IR = false;
//pos[22].ar_centre_IR = false;
}
else
{
pos[0].X = -87;
pos[0].Y = 95;
pos[0].Theta_rotation = 0;
pos[0].choix_fonction = 1;
pos[0].av_droit_IR = false;
pos[0].av_gauche_IR = false;
pos[0].ar_droit_IR = false;
pos[0].ar_gauche_IR = false;
pos[0].ar_centre_IR = false;
}
  
fermetureCanne(3);
etape--;
  Serial.println("init fini");
}

void loop()
{
  analogWrite(A15, 255);
  if(analogRead(A14)==1023)
  {
    Serial.print(1);
  }
  else
  {
    analogWrite(A13, 255);
    switch (pos[etape].choix_fonction)
    {
      case 1:
      if ((detect_obstacle (2) == pos[etape].av_droit_IR && pos[etape].av_droit_IR == true)  || (detect_obstacle (3) == pos[etape].av_gauche_IR && pos[etape].av_gauche_IR == true) || (detect_obstacle (4) == pos[etape].ar_droit_IR && pos[etape].ar_droit_IR == true) || (detect_obstacle (0) == pos[etape].ar_gauche_IR && pos[etape].ar_gauche_IR == true) || (detect_obstacle (1) == pos[etape].ar_centre_IR && pos[etape].ar_centre_IR == true))
      {
        qik.setBrakes(127,127);
        delay(100);     
      }

      else
      {
         avancer(pos[etape].X , pos[etape].Y, pos[etape].Theta_rotation);
         Affichage();
      }
      break;
      case 2:
      rotation(pos[etape].Theta_rotation);
      Affichage();
      break;
      case 3:
      ouverturePelleteuse(1);
      Affichage();
      break;
      case 4:
      fermeturePelleteuse(1);
      Affichage();
      break;
      case 7:
      ouvertureCanne(3);
      Affichage();
      delay(2000);
      break;
      case 8:
      fermetureCanne(3);
      Affichage();
      break;
      case 9:
      fin();
      Affichage();
      break;
      case 10:
      reculer(pos[etape].X , pos[etape].Y, pos[etape].Theta_rotation);
      Affichage();
      break;
      case 11:
      ouvertureMoitier(3);
      Affichage();
      delay(3000);
      break;
      case 12:
      timer1.run();
      break;
      case 13:
      delai();
      break;
      
    }
  }
}

/* ROUTINE DE SERVICE POUR LES INTERRUPTIONS DES VOIX A ET B DES CODEURS DROIT ET GAUCHE */
/********************************    DROIT     *******************************************/
// Routine de service d'interruption attachée à la voie A du codeur incrémental DROIT
void GestionInterruptionCodeurPinA_DR()
{
  if (digitalReadFast2(VOIXA_DROITE) == digitalReadFast2(VOIXB_DROITE))
  {
    ticks_R++;
  }
  else
  {
    ticks_R--;
  }
}
// Routine de service d'interruption attachée à la voie B du codeur incrémental DROIT
void GestionInterruptionCodeurPinB_DR()
{
  if (digitalReadFast2(VOIXB_DROITE) == digitalReadFast2(VOIXA_DROITE))
  {
    ticks_R--;
  }
  else
  {
    ticks_R++;
  }
}

/*******************************GAUCHE**********************************************
 Routine de service d'interruption attachée à la voie A du codeur incrémental GAUCHE*/
void GestionInterruptionCodeurPinA_GA()
{
  if (digitalReadFast2(VOIXA_GAUCHE) == digitalReadFast2(VOIXB_GAUCHE))
  {
    ticks_L--;
  }
  else
  {
    ticks_L++;
  }
}
// Routine de service d'interruption attachée à la voie B du codeur incrémental GAUCHE
void GestionInterruptionCodeurPinB_GA()
{
  if (digitalReadFast2(VOIXB_GAUCHE) == digitalReadFast2(VOIXA_GAUCHE))
  {
    ticks_L++;
  }
  else
  {
    ticks_L--;
  }
}

/***********************Calcul de x et y ***************************************************
  Cette fonction recupere les 2 variables dist_R et dist_L et actualise les valeurs de X et Y
  Les variables dist_R et dist_L sont actialise par la fonction dist_right() et dist_left()
********************************************************************************************/

void Affichage()
{
/**********************Affichage sur le lcd Moniteur*******************************/

  Serial.print("etape =");
  Serial.print(etape);
  Serial.print("\t dist_R =");
  Serial.print(dist_R);
  Serial.print("\t dist_L =");
  Serial.print(dist_L);
  Serial.print("\t dist =");
  Serial.print(dist);
  Serial.print("\t X =");
  Serial.print(X);
  Serial.print("\t Y =");
  Serial.print(Y);
  Serial.print("\t Theta =");
  Serial.print(Theta);
  Serial.print("\t consigne_dist = ");
  Serial.print(consigne_dist);
  Serial.print("\t Theta_direction =");
  Serial.print(Theta_direction);
  Serial.print("\t dDirection = ");
  Serial.print(dDirection);
  Serial.print("\t");
  Serial.print("s = ");
  Serial.print(s);
  Serial.print("\t");
  
//  Serial.print("Commande_L = ");
//  Serial.print(commande_L);
//  Serial.print("\t");
//  Serial.print("Commande_R = ");
//  Serial.print(commande_R);
//  Serial.print("\t");

/******************* Test des infrarouge ***********************/
   for (int i=0;i<5;i++)
  {
    Serial.print(i);
    if ( detect_obstacle(i)==true)
    {
      Serial.print("X");
    }
    else
    {
      Serial.print("N");
    }
  }
  Serial.println();
}


void avancer(float consigne_X, float consigne_Y,float Theta_rotation)   
{
  dist_L = ticks_L * tick_cm;
  dist_R = ticks_R * tick_cm;
  dist = (dist_R + dist_L)/2; // Position robot au centre de l'axe des roues
  d_dist = dist - dist_pre;
  dist_pre = dist;

  Theta = (Theta_ini + (dist_R - dist_L)/ecart_roue)*degreePerRad;
  Theta_direction=(degreePerRad*atan2(((consigne_X - X)),((consigne_Y - Y))));
//  if(consigne_X - X < 0 && consigne_Y - Y > 0)
//  {
//    Theta_direction *= -1;
//  }
//  else if(consigne_X - X < 0 && consigne_Y - Y < 0)
//  {
//    Theta_direction *= 1;    
//  }
//  else if(consigne_X - X > 0 && consigne_Y - Y < 0)
//  {
//    Theta_direction -= 90;
//  }
//  else if(consigne_X - X < 0 && consigne_Y - Y < 0)
//  {
//    Theta_direction *= -1;
//    Theta_direction += 90;
//  }

  dX = d_dist * sin(Theta/degreePerRad);
  dY = d_dist * cos(Theta/degreePerRad);

  X += - dX;
  Y += -dY;

  s = sqrt(pow((X-X0),2)+pow((Y-Y0),2)); 
  consigne_dist=fabs(sqrt(pow((consigne_X-X0),2)+pow((consigne_Y-Y0),2))-s);

/********************* Régulation angulaire ***********************/

  dDirection = Theta_direction - Theta;
  if (dDirection < 0)
  {
    dDirection = -100*(1-exp(-fabs(dDirection)/90));
  }
  else
  {
    dDirection = 100*(1-exp(-fabs(dDirection)/90));
  }
  angle_R=-dDirection;
  angle_L=dDirection;
  
/******************* Régulation en vitesse ************************/

  if(consigne_dist<20)
  { 
    regulation_vitesse=6*consigne_dist+40;
  }
  else if (s<20)
  {
    regulation_vitesse=6*s+40;
  }
  else
  {
    regulation_vitesse=150;
  }

/******************** Valeurs des coefficient ************************/

  Kp_R=0.2;
  Kp_L=0.2;  
  Kp_angle_R = 0.8;
  Kp_angle_L = 0.8;
  
/******************** Commandes moteur ********************************/
 
  commande_R = regulation_vitesse * Kp_R + angle_L * Kp_angle_L+5;
  commande_L = regulation_vitesse * Kp_L + angle_R * Kp_angle_R+5;

/******************** Condition d'arrêt *******************************/

  if(fabs(consigne_X - X) < 4 && fabs(consigne_Y - Y) < 4)
  {
    qik.setBrakes(127,127);
    X0 = pos[etape].X;
    Y0 = pos[etape].Y;
    etape++;
  }
  
  else 
  {
    //qik.setSpeeds(commande_L,commande_R);
    qik.setM0Speed(-commande_L);
    qik.setM1Speed(commande_R);
  }
}

void reculer(float consigne_X, float consigne_Y,float Theta_rotation)   
{
  dist_L = ticks_L * tick_cm;
  dist_R = ticks_R * tick_cm;

  dist = (dist_R + dist_L)/2; // Position robot au centre de l'axe des roues
  d_dist = dist - dist_pre;
  dist_pre = dist;

  Theta = (Theta_ini + (dist_R - dist_L)/ecart_roue)*degreePerRad;
  Theta_direction=degreePerRad*atan(((consigne_X - X))/((consigne_Y - Y)));
  
  dX = d_dist * sin(Theta/degreePerRad);
  dY = d_dist * cos(Theta/degreePerRad);

  X += -dX;
  Y += -dY;

  s = sqrt(pow((X-X0),2)+pow((Y-Y0),2)); 
  consigne_dist=fabs(sqrt(pow((consigne_X-X0),2)+pow((consigne_Y-Y0),2))-s);

/********************* Régulation angulaire ***********************/

  dDirection = Theta_direction - Theta;
  if (dDirection < 0)
  {
    dDirection = -100*(1-exp(-fabs(dDirection)/60));
  }
  else
  {
    dDirection = 100*(1-exp(-fabs(dDirection)/60));
  }
  angle_R=dDirection;
  angle_L=-dDirection;
  
/******************* Régulation en vitesse ************************/

  if(consigne_dist<20)
  { 
    regulation_vitesse= 6*consigne_dist+40;
  }
  else if (s<20)
  {
    regulation_vitesse=6*s+40;
  }
  else
  {
    regulation_vitesse=150;
  }

/******************** Valeurs des coefficient ************************/

  Kp_R=0.2;
  Kp_L=0.2;  
  Kp_angle_R =0.8;
  Kp_angle_L =0.8;
  
/******************** Commandes moteur ********************************/
 
  commande_R = regulation_vitesse * Kp_R + angle_L * Kp_angle_L+5;
  commande_L = regulation_vitesse * Kp_L + angle_R * Kp_angle_R+5;

/******************** Condition d'arrêt *******************************/

  if(fabs(consigne_X - X) < 4 && fabs(consigne_Y - Y) < 4)
  {
    qik.setBrakes(127,127);
    X0 = pos[etape].X;
    Y0 = pos[etape].Y;
    etape++;
  }
  
  else 
  {
    //qik.setSpeeds(commande_L,commande_R);
    qik.setM0Speed(commande_L);
    qik.setM1Speed(-commande_R);
  }
}

void rotation (float Theta_rotation) 
{
  dist_L = ticks_L * tick_cm;
  dist_R = ticks_R * tick_cm;

  dist = (dist_R + dist_L)/2; // Position robot au centre de l'axe des roues
  d_dist = dist - dist_pre;
  dist_pre = dist;

  Theta = (Theta_ini + (dist_R - dist_L)/ecart_roue)*degreePerRad;
   
  dX = d_dist * sin(Theta/degreePerRad);
  dY = d_dist * cos(Theta/degreePerRad);

  X += -dX;
  Y += dY;

/********************* Régulation angulaire ***********************/

  dDirection = Theta_rotation - Theta;
  if (dDirection < 0)
  {
    dDirection = -100*(1-exp(-fabs(dDirection)/80));
  }
  else
  {
    dDirection = 100*(1-exp(-fabs(dDirection)/80));
  }
  angle_R=-dDirection;
  angle_L=dDirection;

/******************** Valeurs des coefficient ************************/

  Kp_angle_R =0.55;
  Kp_angle_L =0.55;

/******************** Commandes moteur ********************************/

  commande_R = angle_L * Kp_angle_L;
  commande_L = angle_R * Kp_angle_R;

/******************** Condition d'arrêt *******************************/

  if(fabs(Theta_rotation - Theta) < 10)
  {
   X0 = pos[etape].X;
   Y0 = pos[etape].Y;
   qik.setBrakes(127,127);
   etape++;
  }
   else 
  {
    //qik.setSpeeds(commande_L,commande_R);
    qik.setM0Speed(-commande_L);
    qik.setM1Speed(commande_R);
  }
}

void ouvertureBras(int ID)
{
  //Dynamixel2.move(ID ,510);
  etape++;
}

void ouvertureCanne(int ID)
{
  //Dynamixel2.moveSpeed(ID ,520,300);
  etape++;
}

void ouvertureMoitier(int ID)
{
  //Dynamixel2.moveSpeed(ID ,320,100);
  etape++;
}

void fermetureCanne(int ID)
{
  //Dynamixel2.moveSpeed(ID ,200,300);
  etape++;
}

void fermetureBras(int ID)
{
  //Dynamixel2.move(ID,830);
  etape++;
}

void fermetureParassol(int ID)
{
  //Dynamixel2.moveSpeed(ID,0, 30);
  etape++;
}

void ouvertureParassol(int ID)
{
  //Dynamixel2.moveSpeed(ID,130, 30);
  etape++;
}

void fermeturePelleteuse(int ID)
{
  Serial.println("ok");/*
  Dynamixel2.turn(ID,true,500);
  Dynamixel2.turn(ID+1,false,500);
  delay(500);
  Dynamixel2.turn(ID,true,0);
  Dynamixel2.turn(ID+1,true,0);*/
  etape++;
}

void ouverturePelleteuse(int ID)
{ 
  /*Dynamixel2.turn(ID,false,500);
  Dynamixel2.turn(ID+1,true,500);
  delay(500);
  Dynamixel2.turn(ID,false,0);
  Dynamixel2.turn(ID+1,false,0);*/
  etape++; 
}
void fin()
{
  qik.setBrakes(127,127);
  while(1)
  {
    Affichage();
  }
}
boolean detect_obstacle (int sensor)
{
 if (analogRead(sensor) > 250) //mettre digitalRead(sensor) pour les capteurs numériques
 return true;
 else
 return false;
}
void delai()
{
  delay(1000);
}


