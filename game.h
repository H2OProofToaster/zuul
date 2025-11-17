#ifndef GAME_H
#define GAME_H

#include "inventory.h"
#include "room.h"
#inlcude <map>

class Game
{
 public:
  Game();
  
 private:
  Inventory::Inventory* inventory;
  int winNum;
  map<string, Room::Room*> rooms;
  
#endif
