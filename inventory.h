#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include <vector>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/


class Inventory
{
 private:
  vector<Item::Item*> items;

 public:
  Inventory();
  void addItem(char* name, char* description, char* solutionRoom, char* solutionText);
  void removeItem(char* name);
  Item::Item* getItem(char* name);
  vector<Item::Item*> getItems();
}

#endif
