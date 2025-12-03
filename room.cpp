#include "room.h"
#include <map>
#include <cstring>
#include "inventory.h"
#include <iostream>
#include "item.h"
#inlcude <vector>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

Room::Room(char* descriptionIn)
{
  strcpy(description, descriptionIn);
  inventory = new Inventory();
}

void Room::addItem(char* name, char* description, char* solutionRoom, char* solutionText)
{ inventory.addItem(name, description, solutionRoom, solutionText); }

void Room::setExit(char* direction, Room* neighbor)
{ exits[direction] = neighbor; }

char* getShortDescription()
{ return Room::description; }

void printLongDescription()
{
  std::cout << "You are " << Room::description << "." << std::endl;

  //Modified from w3schools.com
  for(int i = Room::exits.begin(); i != Room::exits.end(); i++)
    {
      if(i == Room::exits.end()) { std::cout << i->first; }
      std::cout << i->first << ", ";
    }
}

Room* getExit(char* direction)
{ return Room::exits[direction]; }

Item* getItem(char* name)
{ return Room::inventory.getItem(name); }

std::vector<Item*> getItems()
{ return Room::inventory.getItems(); }
