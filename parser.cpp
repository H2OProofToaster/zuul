#include "parser.h"
#include "commandWords.h"
#include "command.h"
#include <iostream>
#include <cstring>

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

using namespace std;

Parser::Parser()
{ commands = new CommandWords(); }

Command* Parser::getCommand()
{
  //Input
  char inputLine[40];

  //Get input
  cout << endl;
  cout << "> ";
  cin.get(inputLine, 40);

  //Get first space position
  char* spacePos = strchr(inputLine, ' '); //ASCII for " " is 32, unused now

  char* word1 = inputLine;
  char* word2 = nullptr;

  //Check for one word
  if(!spacePos)
  {
    strcpy(word1, inputLine);
    if (commands->isCommand(word1)) { return new Command(word1, nullptr); } //Single word command (help)
    else { return new Command(nullptr, nullptr); } //Nothing was typed
  }

  //End word1
  *spacePos = '\0'; //Idea from ChatGPT 7/12/25

  //Set word 2
  word2 = spacePos + 1;

  cin.ignore();

  //Check if command and return
  if(commands->isCommand(word1))
    { return new Command(word1, word2); } //Command exists, return new command
  else
    { return new Command(nullptr, nullptr); } //Command doesn't exist, return null command

}

void Parser::showCommands()
{ commands->showAll(); }
