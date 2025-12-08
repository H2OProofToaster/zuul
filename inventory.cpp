#include "inventory.h"
#include "item.h"
#include <vector>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

Inventory::Inventory()
{
  items = new std::vector<Item*>;
}

//Adds items with a name, description, the room it's used in, and the win text
void Inventory::addItem(char* name, char* description, char* solutionRoom, char* solutionText)
{
  this->items->push_back(new Item(name, description, solutionRoom, solutionText));
}

void Inventory::addItem(Item* item)
{
  this->items->push_back(item);
}

//Removes an item from an inventory
void Inventory::removeItem(char* name)
{
  for(int i = 0; i < this->items->size(); i++)
    {
      if(strcmp(this->items->at(i)->getName(), name) == 0)
	{
	  delete this->items->at(i);
	  this->items->erase(this->items->begin() + i);
	}
    }
}

//Takes in another inventory ptr and switches where the item ptr is
void Inventory::moveItem(Inventory* inventory, Item* item)
{
  items->push_back(item);
  inventory->removeItem(item->getName());
}

//Just for printing and stuff
Item* Inventory::getItem(char* name)
{
  for(int i = 0; i < this->items->size(); i++)
  {
    if(strcmp(this->items->at(i)->getName(), name) == 0) { return this->items->at(i); }
  }
}

std::vector<Item*> Inventory::getItems()
{ return *(this->items); }
