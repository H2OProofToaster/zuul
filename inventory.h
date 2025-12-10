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
  std::vector<Item*>* items;

 public:
  Inventory();
  void addItem(char* name, char* description, char* solutionRoom, char* solutionText);
  void addItem(Item* item);
  void removeItem(char* name);
  void moveItem(Inventory* inventory, Item* item);
  Item* getItem(char* name);
  void showItems();
  std::vector<Item*> getItems();
};

#endif
