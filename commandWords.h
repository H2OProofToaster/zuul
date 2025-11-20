#ifndef COMMANDWORDS_H
#define COMMANDWORDS_H
#include <vector>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

class CommandWords
{
 private:
  //A constant array that holds all valid command words
  vector<const char*> validCommands = {"go", "quit", "help", "use", "drop", "pickup", "inventory"};

 public:
  CommandWords();

  bool isCommand(char* aString);
  void showAll();
}

#endif
