#include "room.h"
#include <map>
#include <cstring>
#include "inventory.h"

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

Room::Room(char* descriptionIn)
{
  strcpy(description, descriptionIn);
  inventory = new Inventory::Inventory();
}

void Room::addItem(char* name, char* description, char* solutionRoom, char* solutionText)
{ inventory.addItem(name, description, solutionRoom, solutionText); }

void Room::setExit(char* direction, Room* neighbor)
{ exits[direction] = neighbor; }

char* getShortDescription()
{ return description }

void printLongDescription()
{
  //I don't wanna do this today, remember combined with setExitString from python
  return
}
