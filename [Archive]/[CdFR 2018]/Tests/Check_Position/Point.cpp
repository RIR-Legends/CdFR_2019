#include "Point.h"

Point::Point()
{
  x = 0;
  y = 0;
  theta = 0;
}

Point::Point(float X = 0.0, float Y = 0.0, float Theta = 0.0)
{
  x = X;
  y = Y;
  theta = Theta;
}

float Point::X() { return x; }

float Point::Y() { return y; }

float Point::Theta() { return theta; }

void Point::AfficherPosition()
{
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("mm\tY = ");
  Serial.print(y);
  Serial.print("mm\tTheta = ");
  Serial.print(theta);
  Serial.println("rad");
}

//NormerTheta
