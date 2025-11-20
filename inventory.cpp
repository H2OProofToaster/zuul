#include "inventory.h"
#include <vector>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

Inventory::Inventory() {}

//Adds items with a name, description, the room it's used in, and the win text
void Inventory::addItem(char* name, char* description, char* solutionRoom, char* solutionText)
{
  items.push_back(new Item::Item(name, description, solutionRoom, solutionText)*);
}

//I don't wanna do this
void Inventory::removeItem(char* name)
{
  for(int i = 0; i < items.size(); i++)
    {
      if(strcmp(items[i]->getName(), name) == 0)
	{
	  delete items[i];
	  items.erase(items.begin() + i);
	}
    }
}

