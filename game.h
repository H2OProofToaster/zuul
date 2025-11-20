#ifndef GAME_H
#define GAME_H

#include "inventory.h"
#include "room.h"
#inlcude <map>
#inlcude "command.h"

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

class Game
{
 public:
  Game();
  void play();
  
 private:
  //Holds items
  Inventory::Inventory* inventory;
  int winNum;

  //Holds rooms
  map<string, Room::Room*> rooms;

  void printWelcome();
  bool processCommand(Command::Command* command);
  void useItem(Command::Command* command);
  void createRooms();
  void printHelp();
  void goRoom(Command::Command* command);
  bool quitGame(Command::Command* command);
  
#endif
