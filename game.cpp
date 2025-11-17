#include "commandWords.h"
#include "command.h"
#include "parser.h"
#include "room.h"
#include "inventory.h"
#include <map>

using namespace std;

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

Parser::Parser* Game::parser = new Parser::Parser();
Room::Room* Game::currentRoom;

Game::Game()
{
  Game::createRooms();
  Inventory::Inventory* Game::inventory = new Inventory::Inventory();
  Game::winNum = 0;
}

void Game::createRooms()
{
  //Create the rooms

  //Rooms, formatted by ChatGPT 17/11 (idk why it did that)
  Game::rooms.at("myRoom",             new Room("where I sleep"));
  Game::rooms.at("hallway",            new Room("where it's a hallway"));
  Game::rooms.at("sisterRoom",         new Room("where it's pink"));
  Game::rooms.at("parentRoom",         new Room("where my parents sleep"));
  Game::rooms.at("parentBathroom",     new Room("where my parents bathe"));
  Game::rooms.at("parentCloset",       new Room("where it's a closet"));
  Game::rooms.at("laundryRoom",        new Room("where it has a big sink"));
  Game::rooms.at("waterHeaterRoom",    new Room("where it's kinda scary here"));
  Game::rooms.at("upstairsBathroom",   new Room("where my sister's side is messy"));
  Game::rooms.at("office",             new Room("where it's not my office"));
  Game::rooms.at("bonusRoom",          new Room("where it gets hot in here"));
  Game::rooms.at("kitchen",            new Room("where it's food"));
  Game::rooms.at("livingRoom",         new Room("where we live"));
  Game::rooms.at("downstairsBathroom", new Room("where I use it sometimes"));
  Game::rooms.at("guestBedroom",       new Room("where I don't use it sometimes"));
  Game::rooms.at("foyer",              new Room("in the foyer I guess"));
  Game::rooms.at("diningRoom",         new Room("eat here"));
  Game::rooms.at("garage",             new Room("where the popsicles are"));
  Game::rooms.at("wineCellar",         new Room("... well, what do you think is here"));

  //Set exits, formatted by ChatGPT 17/11 (I still don't know why it did that)
  Game::rooms.at("myRoom")->setExit("Hallway",        Game::rooms.at("hallway"));

  Game::rooms.at("hallway")->setExit("My Room",            Game::rooms.at("myRoom"));
  Game::rooms.at("hallway")->setExit("Sister's Room",      Game::rooms.at("sisterRoom"));
  Game::rooms.at("hallway")->setExit("Parent's Room",      Game::rooms.at("parentRoom"));
  Game::rooms.at("hallway")->setExit("Laundry Room",       Game::rooms.at("laundryRoom"));
  Game::rooms.at("hallway")->setExit("Upstairs Bathroom",  Game::rooms.at("upstairsBathroom"));
  Game::rooms.at("hallway")->setExit("Office",        Game::rooms.at("office"));
  Game::rooms.at("hallway")->setExit("Bonus Room",         Game::rooms.at("bonusRoom"));
  Game::rooms.at("hallway")->setExit("Kitchen",       Game::rooms.at("kitchen"));

  Game::rooms.at("sisterRoom")->setExit("Hallway",    Game::rooms.at("hallway"));

  Game::rooms.at("parentRoom")->setExit("Hallway",        Game::rooms.at("hallway"));
  Game::rooms.at("parentRoom")->setExit("Parent's Bathroom",   Game::rooms.at("parentBathroom"));

  Game::rooms.at("parentBathroom")->setExit("Parent's Room",        Game::rooms.at("parentRoom"));
  Game::rooms.at("parentBathroom")->setExit("Parent's Closet", Game::rooms.at("parentCloset"));

  Game::rooms.at("parentCloset")->setExit("Parent's Bathroom",  Game::rooms.at("parentBathroom"));

  Game::rooms.at("laundryRoom")->setExit("Hallway",      Game::rooms.at("hallway"));
  Game::rooms.at("laundryRoom")->setExit("Water Heater Room", Game::rooms.at("waterHeaterRoom"));

  Game::rooms.at("waterHeaterRoom")->setExit("Laundry Room", Game::rooms.at("laundryRoom"));

  Game::rooms.at("upstairsBathroom")->setExit("Hallway", Game::rooms.at("hallway"));

  Game::rooms.at("office")->setExit("Hallway", Game::rooms.at("hallway"));

  Game::rooms.at("bonusRoom")->setExit("Hallway", Game::rooms.at("hallway"));

  Game::rooms.at("kitchen")->setExit("Hallway",      Game::rooms.at("hallway"));
  Game::rooms.at("kitchen")->setExit("Living Room",       Game::rooms.at("livingRoom"));
  Game::rooms.at("kitchen")->setExit("Dining Room",       Game::rooms.at("diningRoom"));
  Game::rooms.at("kitchen")->setExit("Foyer",        Game::rooms.at("foyer"));

  Game::rooms.at("livingRoom")->setExit("Kitchen",          Game::rooms.at("kitchen"));
  Game::rooms.at("livingRoom")->setExit("Wine Cellar",             Game::rooms.at("wineCellar"));
  Game::rooms.at("livingRoom")->setExit("Downstairs Bathroom",   Game::rooms.at("downstairsBathroom"));
  Game::rooms.at("livingRoom")->setExit("Guest Bedroom",         Game::rooms.at("guestBedroom"));

  Game::rooms.at("downstairsBathroom")->setExit("Living Room", Game::rooms.at("livingRoom"));

  Game::rooms.at("guestBedroom")->setExit("Living Room", Game::rooms.at("livingRoom"));

  Game::rooms.at("wineCellar")->setExit("Living Room", Game::rooms.at("livingRoom"));

  Game::rooms.at("diningRoom")->setExit("Kitchen", Game::rooms.at("kitchen"));
  Game::rooms.at("diningRoom")->setExit("Foyer",   Game::rooms.at("foyer"));

  Game::rooms.at("foyer")->setExit("Kitchen",   Game::rooms.at("kitchen"));
  Game::rooms.at("foyer")->setExit("Garage",    Game::rooms.at("garage"));
  Game::rooms.at("foyer")->setExit("Dining Room",    Game::rooms.at("diningRoom"));

  Game::rooms.at("garage")->setExit("Foyer", Game::rooms.at("foyer"));

  //Add Items
  Game::rooms.at("myRoom")->addItem("Food Note",
				   "You need to get some food:\n1. Gouda Cheese Bites\n2. Brie\n3. Popsicles\nAnd return to your room.",
				   "myRoom",
				   "You have successfully gathered the snacks!\nYou win!");
  Game::rooms.at("hallway")->addItem("Kamala Harris",
				    "A cardboard standee of Kamala Harris.\nAdorned with a rainbow inflatable crown, green gummy bear chains, and a hawaiian shirt.",
				    "None",
				    "None");
  Game::rooms.at("garage")->addItem("Popsicles",
				    "They are of flavor pineapple.",
				    "myRoom",
				    "That was delicious.");
  Game::rooms.at("kitchen")->addItem("Gouda Chese Bites",
				     "There must be something other than cheese in this, I'm addicted.",
				     "myRoom",
				     "That was delicious.");
  Game::rooms.at("kitchen")->addItme("Brie",
				     "A very good melting cheese, enjoy with bread.",
				     "myRoom",
				     "That was delicious.");

  Game::currentRoom = Game::rooms.at("foyer");
