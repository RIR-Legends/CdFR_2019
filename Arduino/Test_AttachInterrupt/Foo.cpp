#include "Foo.h"
#include <TimerOne.h>

int Foo::Compteur = 0;
Foo::Foo(){
}

void Foo::Setup(){
  Timer1.initialize(800);
  Timer1.attachInterrupt(Action);
}

void Foo::Action(){
  Compteur++;
}

int Foo::Return_Compteur(){
  return Compteur;
}
