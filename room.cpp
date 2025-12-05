#include "room.h"
#include <map>
#include <cstring>
#include "inventory.h"
#include <iostream>
#include "item.h"
#include <vector>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

Room::Room(char* descriptionIn)
{
  this->description = descriptionIn;
  this->inventory = new Inventory();
}

void Room::addItem(char* name, char* description, char* solutionRoom, char* solutionText)
{ this->inventory->addItem(name, description, solutionRoom, solutionText); }

void Room::removeItem(char* name)
{ this->inventory->removeItem(name); }

void Room::setExit(char* direction, Room* neighbor)
{ this->exits[direction] = neighbor; }

char* Room::getShortDescription()
{ return this->description; }

void Room::printLongDescription()
{
  std::cout << "You are " << this->description << "." << std::endl;

  //Modified from w3schools.com
  for(auto i = this->exits.begin(); i != this->exits.end(); i++)
    {
      if(i == this->exits.end()) { std::cout << i->first; }
      std::cout << i->first << ", ";
    }

  //Newline for parser "<"
  std::cout << std::endl;
}

Room* Room::getExit(char* direction)
{ return this->exits[direction]; }

Item* Room::getItem(char* name)
{ return this->inventory->getItem(name); }

std::vector<Item*> Room::getItems()
{ return this->inventory->getItems(); }
