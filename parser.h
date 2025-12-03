#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "command.h"
#include "commandWords.h"

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

class Parser
{
 public:
  Parser();
  Command* getCommand();
  void showCommands();

 private:
  CommandWords commands;
};

#endif
