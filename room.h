#ifndef ROOM_H
#define ROOM_H

#include <cstring>
#include <map>
#include "inventory.h"
#include "item.h"
#include <vector>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

class Room
{
 public:
  Room(char* descriptionIn);
  void addItem(char* name, char* description, char* solutionRoom, char* solutionText);
  void removeItem(char* name);
  void setExit(char* direction, Room* neighbor);
  char* getShortDescription();
  void printLongDescription();
  Room* getExit(char* direction);
  Item* getItem(char* name);
  std::vector<Item*> getItems();
  
 private:
  std::map<char*, Room*> exits;
  char* description;
  Inventory* inventory;
};

#endif
