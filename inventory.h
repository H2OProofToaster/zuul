#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include <vector>

class Inventory
{
 private:
  vector<Item::Item*> items;

 public:
  Inventory();
  void addItem(char* name, char* description, char* solutionRoom, char* solutionText);
  void removeItem(char* name);
  Item::Item* getItem(char* name);
}

#endif
