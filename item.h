#ifndef ITEM_H
#define ITEM_H

#include <cstring>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/


//An item that has a name, description, a room to be used in, and text displayed upon proper usage
class Item
{
 public:
  Item(char* nameIn, char* descriptionIn, char* solutionRoomIn, char* solutionTextIn);
  char* getName();
  char* getDescription();
  char* getSolutionRoom();
  char* getSolutionText();

 private:
  char* name;
  char* description;
  char* solutionRoom;
  char* solutionText;
};

#endif
