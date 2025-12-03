#ifndef COMMANDWORDS_H
#define COMMANDWORDS_H
#include <vector>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

class CommandWords
{
 public:
  //A constant array that holds all valid command words
  std::vector<const char*> validCommands = {"go", "quit", "help", "use", "drop", "pickup", "inventory"};

  CommandWords();

  bool isCommand(char* aString);
  void showAll();
};

#endif
