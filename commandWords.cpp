#include "commandWords.h"
#include <vector>
#include <iostream>

using namespace std;

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

//Initialize the command words
CommandWords::CommandWords() {}

//Check whether a given string is a valid command words, return true if it is, false if it isn't
bool CommandWords::isCommand(char* aString)
{
  for(int i = 0; i < validCommands.size(); i++)
    {
      if(strcmp(validcommands[i], aString) == 0) { return true; }
    }

  //If we get here, the string was not found in the commands
  return false;
}

//Print all valid commands
void CommandWords::showAll()
{
  for(int i = 0; i < validCommands.size(); i++) { cout << *(validCommands[i]) << "  "; }
  cout << "\n";
}
