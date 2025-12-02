#include "parser.h"
#include "commandWords.h"
#include "command.h"
#include <iostream>
#include <cstring>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

Parser::Parser()
{ commands = new CommandWords::commandWords(); }

Command::Command* getCommand()
{
  //Tokenize
  char inputLine[40];
  
  std::cout << "> ";
  std::cin.get(21, inputLine);

  char word1[10];
  char word2[30];
  
  char* firstSpace = strchr(inputLine, " ");
  
  
  //Get word 1

  //Get word 2

  //Check if command and return
}
