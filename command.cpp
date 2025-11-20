#include "command.h"

using namespace std;

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

//Create a command object, first and second word must be supplied, but either one (or both) can be null
//The command word should be null to indicate that this was a command that is not recognised by this game
Command::Command(char* first, char* second)
  : commandWord{ first }
  , secondWord{ second }
{}

//Return the command word (the first word) of this command, if the command was not understood, the result is null
char* Command::getCommandWord() { return commandWord; }

//Return the second word of this command, returns null if there was no second word
char* Command::getSecondWord() { return secondWord; }

//Return true if this command was not understood
bool Command::isUnknown() { return commandWord == NULL; }

//Return true if the command has a second word
bool Command::hasSecondWord() { return secondWord != NULL; }
