#include "Stage.h"

Stage::Stage()
{
  MaxStage = 11;
  CurrentStage = 0;
  actionHere = false;
}

void Stage::SetupAll(bool GreenSide)
{
  //Penser à changer le Stage.h
  MaxStage = 11;
  CurrentStage = 0;

  //Dégagement
  Stages[0] = !GreenSide ? Point(210, 465, PI / 4) : Point(210, 465, 3 * PI / 4);

  //Loin les cubes
  Stages[1] = Point(845, 1100, -PI / 2);
  //Devant les cubes
  Stages[2] = Point(840, 805, -PI / 2);
  //Depose des cubes
  Stages[3] = Point(730, 330, -PI / 2);

  //Degagement
  Stages[4] = !GreenSide ? Point(730, 490, 5 * PI / 6) : Point(730, 490, PI / 6);

  //Eau
  Stages[5] = !GreenSide ? Point(300, 850, PI / 2) : Point(300, 850, -PI / 2);

  //Loin les cubes
  Stages[6] = Point(300, 900, PI / 2);
  //Devant les cubes
  Stages[7] = Point(300, 1005, PI / 2);
  Stages[8] = Point(300, 1005, PI - 0.3);
  Stages[9] = Point(300, 1005, (3 * PI / 2) - 0.4);
  //Depose des cubes
  Stages[10] = Point(600, 330, -PI / 2);
  //Degagement
  Stages[11] = !GreenSide ? Point(600, 490, -PI / 2) : Point(600, 490, -PI / 2);

  if (GreenSide)//cote vert
    for (int i = 0 ; i <= MaxStage ; i++)
      Stages[i] = Point(3000 - Stages[i].X(), Stages[i].Y(), Stages[i].Theta());
}

Point Stage::NextStage()
{
  actionHere = false;
  if (CurrentStage == 0)
    delay(30000);
  if (CurrentStage < MaxStage)
  {
    CurrentStage++;
    actionHere = EndMove(CurrentStage);
  }
  else if (CurrentStage == MaxStage + 1)
    actionHere = true;
  return Stages[CurrentStage];
}

bool Stage::EndMove(short stage)
{
  //Si le prochain stage, càd la prochaine position est à la suite d'une action (de la board master), alors il faut que l'action s'effectue avant
  return (stage != 1 && stage != 5 && stage != 9 && stage != 10);
}

bool Stage::ActionHere()
{
  return actionHere;
}

Point Stage::FirstPoint()
{
  return Stages[0];
}
