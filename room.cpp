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
  inventory = new Inventory::Inventory();
}

void Room::addItem(char* name, char* description, char* solutionRoom, char* solutionText)
{ inventory.addItem(name, description, solutionRoom, solutionText); }

void Room::setExit(char* direction, Room* neighbor)
{ exits[direction] = neighbor; }

char* getShortDescription()
{ return description; }

void printLongDescription()
{
  std::cout << "You are " << description << "." << endl;

  //Modified from w3schools.com
  for(int i = exits.begin(); i != exits.end(); i++)
    {
      if(i == exits.end()) { std::cout << i->first; }
      std::cout << i->first << ", ";
    }
}

Room* getExit(char* direction)
{ return exits[direction]; }

Item* getItem(char* name)
{ return inventory.getItem(name); }

vector<Item::Item*> getItems()
{ return inventory.getItems(); }
