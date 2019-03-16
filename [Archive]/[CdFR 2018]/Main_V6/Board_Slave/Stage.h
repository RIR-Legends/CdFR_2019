#include "Arduino.h"
#include "Point.h"

class Stage
{
  public:
  Stage();
  void SetupAll(bool);
  Point NextStage();
  Point FirstPoint();
  bool ActionHere();

  private:
  short MaxStage;
  short CurrentStage;
  bool actionHere;
  Point Stages[12]; //MaxStage + 1
  bool EndMove(short);
};

