#include "game.h"

/*
  Nick Helbling
  10/12/1015
  A little adventure game
  use "go" + room to go to a room
  use "pickup"/"drop"/"use" + item to do that to an item
  use "help" to show commands
  use "quit" to exit
  Quick solution
  1. Go to garage, get popsicles
  2. Go to kitchen, get gouda chese bites (yes it's spelled wrong), get brie
  3. Go to hallway
  4. Go to myRoom, get food note, use all food, then use food note
*/

int main() {
  Game* g = new Game();
  g->play();
}
