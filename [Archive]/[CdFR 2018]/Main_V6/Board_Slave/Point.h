#ifndef POINT_H
#define POINT_H
#include "Arduino.h"

class Point
{
  public:
  Point();
  Point(float, float, float);
  float X();
  float Y();
  float Theta();
  void AfficherPosition();
  static float NormTheta(float);
    
  private:
  float x;
  float y;
  float theta;
};
#endif
