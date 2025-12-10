#include "inventory.h"
#include "item.h"
#include <vector>
#include <iostream>

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
  std::vector<Item*>::iterator it;
  for(it = items->begin(); it != items->end(); ++it)
    {
      if((*it)->getName() == name)
	{
	  items->erase(it);
	  std::cout << items->size();
	  break;
	}
    }
}

void Inventory::moveItem(Inventory* inventory, Item* item)
{
  std::cout << "Self inventory:";
  this->showItems();
  std::cout << "Other inventory:";
  inventory->showItems();

  items->push_back(item); //Puts item ptr in called inventory's inventory

  std::cout << "Self inventory:";
  this->showItems();
  std::cout << "Other inventory:";
  inventory->showItems();

  inventory->removeItem(item->getName());
  
  std::cout << "Self inventory:";
  this->showItems();
  std::cout << "Other inventory:";
  inventory->showItems();
}

//Just for printing and stuff
Item* Inventory::getItem(char* name)
{
  std::vector<Item*>::iterator it;
  for(it = items->begin(); it != items->end(); ++it)
  {
    if(strcmp((*it)->getName(), name) == 0) { return *it; }
  }
}

void Inventory::showItems()
{
  std::vector<Item*>::iterator it;
  for(it = items->begin(); it != items->end(); ++it)
    {
      std::cout << (*it)->getName();
    }
}

std::vector<Item*> Inventory::getItems()
{ return *(this->items); }
