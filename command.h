#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

class Command
{
 public:
  char* commandWord;
  char* secondWord;
  
  Command(char* first, char* second);
  char* getCommandWord();
  char* getSecondWord();
  bool isUnknown();
  bool hasSecondWord();
};

#endif
