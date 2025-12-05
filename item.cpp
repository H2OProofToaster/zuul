#include "item.h"
#include <cstring>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/


Item::Item(char* nameIn, char* descriptionIn, char* solutionRoomIn, char* solutionTextIn)
{
  this->name = nameIn;
  this->description = descriptionIn;
  this->solutionRoom = solutionRoomIn;
  this->solutionText = solutionTextIn;
}


char* Item::getName() { return name; }
char* Item::getDescription() { return description; }
char* Item::getSolutionRoom() { return solutionRoom; }
char* Item::getSolutionText() { return solutionText; }
