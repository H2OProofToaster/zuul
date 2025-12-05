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
{ commands = new CommandWords(); }

Command* Parser::getCommand()
{
  //Tokenize
  char inputLine[40];
  
  std::cout << "> ";
  std::cin.get(inputLine, 21);

  char word1[10];
  char word2[30];
  
  char* firstSpace = strchr(inputLine, 32); //ASCII for " "

  //Messing around I found that the ptr - the str is the index of the last rest of the characters? Idrk how it works
  
  //Get word 1

  strncpy(word1, inputLine, firstSpace - inputLine);

  //Get word 2

  strcpy(word2, firstSpace + 1);

  //Check if command and return
  if(commands->isCommand(word1) == true)
    { return new Command(word1, word2); }
  else
    { return new Command(NULL, word2); }

  //Base return
  return new Command(NULL, NULL);
}

void Parser::showCommands()
{ commands->showAll(); }
