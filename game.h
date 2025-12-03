#ifndef GAME_H
#define GAME_H

#include "inventory.h"
#include "room.h"
#include <map>
#include "command.h"
#include "parser.h"
#include "item.h"

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

class Game
{
 public:
  Game();
  void play();
  static Parser* parser;
  static Room* currentRoom;

  //Holds items
  Inventory* inventory;
  int winNum;

  //Holds rooms
  std::map<std::string, Room*> rooms;

 private:
  void printWelcome();
  bool processCommand(Command* command);
  void useItem(Item* command);
  void createRooms();
  void printHelp();
  void goRoom(Command* command);
  bool quitGame(Command* command);
};
  
#endif
