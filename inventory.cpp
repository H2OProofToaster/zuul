#include "inventory.h"
#include "item.h"
#include <vector>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

Inventory::Inventory() {}

//Adds items with a name, description, the room it's used in, and the win text
void Inventory::addItem(char* name, char* description, char* solutionRoom, char* solutionText)
{
  this->items.push_back(new Item(name, description, solutionRoom, solutionText));
}

//I don't wanna do this
//Removes an item from an inventory
void Inventory::removeItem(char* name)
{
  for(int i = 0; i < this->items.size(); i++)
    {
      if(strcmp(this->items[i]->getName(), name) == 0)
	{
	  delete this->items[i];
	  this->items.erase(this->items.begin() + i);
	}
    }
}

//Returns a pointer to an item with a specific name
Item* Inventory::getItem(char* name)
{
  for(int i = 0; i < this->items.size(); i++)
    {
      if(strcmp(this->items[i]->getName(), name) == 0) { return this->items[i]; }
    }
  return nullptr;
}

std::vector<Item*> Inventory::getItems()
{ return this->items; }
