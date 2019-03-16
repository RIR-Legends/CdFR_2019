#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#include "Arduino.h"
#include "Point.h"

extern const float mmPerTick;
extern const short entreRoues;

class Trajectory
{
  public:
  Trajectory();
  Trajectory(Point);

  Point ComputePosition(short, short);
  short ComputeStep(Point);
  //float ComputeTrajectory(Point); //Verifie régulièrement comment attendre un point donné en rectifiant l'angle de trajectoire.
  bool Rotation();

  
  private:
  Point PositionActuelle;
  bool rotation;
};
#endif
