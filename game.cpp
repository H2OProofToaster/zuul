#include "commandWords.h"
#include "command.h"
#include "parser.h"
#include "room.h"
#include "inventory.h"
#include <map>
#include <cstring>

using namespace std;

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

//Global parser and current room pointer
Parser::Parser* Game::parser = new Parser::Parser();
Room::Room* Game::currentRoom;

//Create the game and intialize its internal map
Game::Game()
{
  Game::createRooms();
  Inventory::Inventory* Game::inventory = new Inventory::Inventory();
  Game::winNum = 0;
}

//Main play routine, loops until end of play
void Game::play()
{
  Game::printWelcome();

  //Enter the main command loop, here we repeatedly read commands and
  //execute them until the game is over
  
  bool finished = false;
  while(!finished)
    {
      Command::Command* command = parser.getCommand();
      finished = processCommand(command);
    }
  cout << "Thank you for playing. Good bye.";
}

//Print out the openening message for the player
void Game::printWelcome()
{
  cout << "\nWelcome to Adventure! \n Adventure is a new, incredibly boring adventure game. \nType 'help' if you need help.\n";
  currentRoom.printLongDescription(); //Just couts internally in room.cpp
}


//Given a command, process the command
//If theis command ends the game, true is returned, otherwise false is returned
bool Game::processCommand(Command::Command* command)
{
  bool wantToQuit = false;

  if(command == NULL) { return false; }

  if(command.isUnknown()) { cout << "I don't know what you mean..."; return false; }

  Command::Command* commandWord = command->getCommandWord();

  if(strcmp(commandWord, "help") == 0) { Game::printHelp(); }
  else if(strcmp(commandWord, "go")) { Game::goRoom(command); }
  else if(strcmp(commandWord, "inventory") == 0)
    {
      for(int i = 0; i < Game::inventory.getItems().size(); i++) { cout << Game::inventory.getItems()[i]->getName(); }
    }
  else if(strcmp(commandWord, "quit") == 0) { wantToQuit = Game::quitGame(command); }
  else if(strcmp(Commandword, "use") == 0) { Game::useItem(Game::inventory.getItem(command->getSecondWord())); }
  else if(strcmp(CommandWord, "drop") == 0)
    {
      if(strcmp(command->getSecondWord(), "") == 0) { cout << "Drop what?"; return wantToQuit; }
      Item::Item* itemTemp = Game::inventory.getItem(command->getSecondWord());
      Game::inventory.removeItem(itemTemp);
      Game::currentRoom.addItem(itemTemp.getName(), itemTemp.getDescription(), itemTemp.getSolutionRoom(), itmeTemp.getSolutionText());
    }
  else if(strcmp(commandWord, "pickup") == 0)
    {
      if(strcmp(command->getSecondWord(), "")) { cout << "Pickup what?"; return wantToQuit; }
      Item::Item* itemTemp = Game::currentRoom.getItem(command->getSecondWord());
      Game::currentRoom.removeItem(itemTemp);
      Game::inventory.addItem(itemTemp.getName(), itemTemp.getDescription(), itemTemp.getSolution(), itemTemp.getSolutionText());
      cout << itemTemp.getDescription();
    }

  return wantToQuit;
}

//Implementations of user commands

//Uses item if in correct room
void useItem(Command::Command* command)
{
  if(command == NULL) { cout << "Use what?"; return; }

  if(strcmp(command.getSolutionRoom(), Game::currentRoom) == 0)
    {
      //Win conditions
      if(strcmp(command.getName(), "Food Note") == 0 and Game::winNum == 3)
	{
	  cout << command.getSolutionText();
	  Game::winNum = 0;
	  return;
	}
      if(strcmp(command.getName(), "Gouda Cheese Bites") == 0 or
	 strcmp(command.getName(), "Brie") == 0 or
	 strcmp(command.getName(), "Popsicles") == 0)
	{
	  Game::winNum += 1;
	}

      cout << command.getSolutionText();
      Game::inventory.removeItem(command);
    }
  else { cout << "You can't use that here"; }
}

//Print out some help information, here we print some stupid cryptic message and a list of all the command
void printHelp()
{
  cout << "You are lost. You are alone. You wander around the school. \nYour command words are:";
  Game::parser.showCommands();
}

//Try to go one directions, if there is an exit, enter the new room, otherwise print an error message
void goRoom(Command::Command* command)
{
  //If there is no second word, we don't know where to go
  if(!command->hasSecondWord()) { cout << "Go where?"; return; }

  Room::Room* nextRoom = Game::currentRoom->getExit(command->getSecondWord());

  //Try to leave current room
  if(nextRoom == NULL) { cout << "There is no door!" }
  else
    {
      Game::currentRoom = nextRoom;
      Game::currentRoom.printLongDescription(); //Just couts internally in room.cpp

      //Prints out items in room, if any
      if(Game::currentRoom.getItems().size() > 0) { cout << "There are items:" }
      for(int i = 0; i < Game::currentRoom.getItems().size(); i++) { cout << Game::currentRoom.getItems()[i].getName(); }
    }
}

//"Quit" was entered, check the rest fo the command we really quit the game
//Return true, if this command quits the game, false otherwise
bool quitGame(Command::Command* command)
{
  if(command->hasSecondWord()) { cout << "Quit what?"; return false; }
  else { return true; }
}

//Create all the rooms and link their exits together
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

  //Set exits, formatted by ChatGPT 18/11 (I still don't know why it did that)

  Game::rooms.at("myRoom")->setExit("Hallway", &(Game::rooms.find("hallway")->second));

  Game::rooms.at("hallway")->setExit("My Room",            &(Game::rooms.find("myRoom")->second));
  Game::rooms.at("hallway")->setExit("Sister's Room",      &(Game::rooms.find("sisterRoom")->second));
  Game::rooms.at("hallway")->setExit("Parent's Room",      &(Game::rooms.find("parentRoom")->second));
  Game::rooms.at("hallway")->setExit("Laundry Room",       &(Game::rooms.find("laundryRoom")->second));
  Game::rooms.at("hallway")->setExit("Upstairs Bathroom",  &(Game::rooms.find("upstairsBathroom")->second));
  Game::rooms.at("hallway")->setExit("Office",             &(Game::rooms.find("office")->second));
  Game::rooms.at("hallway")->setExit("Bonus Room",         &(Game::rooms.find("bonusRoom")->second));
  Game::rooms.at("hallway")->setExit("Kitchen",            &(Game::rooms.find("kitchen")->second));

  Game::rooms.at("sisterRoom")->setExit("Hallway", &(Game::rooms.find("hallway")->second));

  Game::rooms.at("parentRoom")->setExit("Hallway",            &(Game::rooms.find("hallway")->second));
  Game::rooms.at("parentRoom")->setExit("Parent's Bathroom",  &(Game::rooms.find("parentBathroom")->second));

  Game::rooms.at("parentBathroom")->setExit("Parent's Room",     &(Game::rooms.find("parentRoom")->second));
  Game::rooms.at("parentBathroom")->setExit("Parent's Closet",   &(Game::rooms.find("parentCloset")->second));
  
  Game::rooms.at("parentCloset")->setExit("Parent's Bathroom", &(Game::rooms.find("parentBathroom")->second));
  
  Game::rooms.at("laundryRoom")->setExit("Hallway",            &(Game::rooms.find("hallway")->second));
  Game::rooms.at("laundryRoom")->setExit("Water Heater Room",  &(Game::rooms.find("waterHeaterRoom")->second));
  
  Game::rooms.at("waterHeaterRoom")->setExit("Laundry Room", &(Game::rooms.find("laundryRoom")->second));
  
  Game::rooms.at("upstairsBathroom")->setExit("Hallway", &(Game::rooms.find("hallway")->second));
  
  Game::rooms.at("office")->setExit("Hallway", &(Game::rooms.find("hallway")->second));
  
  Game::rooms.at("bonusRoom")->setExit("Hallway", &(Game::rooms.find("hallway")->second));
  
  Game::rooms.at("kitchen")->setExit("Hallway",      &(Game::rooms.find("hallway")->second));
  Game::rooms.at("kitchen")->setExit("Living Room",  &(Game::rooms.find("livingRoom")->second));
  Game::rooms.at("kitchen")->setExit("Dining Room",  &(Game::rooms.find("diningRoom")->second));
  Game::rooms.at("kitchen")->setExit("Foyer",        &(Game::rooms.find("foyer")->second));
  
  Game::rooms.at("livingRoom")->setExit("Kitchen",               &(Game::rooms.find("kitchen")->second));
  Game::rooms.at("livingRoom")->setExit("Wine Cellar",           &(Game::rooms.find("wineCellar")->second));
  Game::rooms.at("livingRoom")->setExit("Downstairs Bathroom",   &(Game::rooms.find("downstairsBathroom")->second));
  Game::rooms.at("livingRoom")->setExit("Guest Bedroom",         &(Game::rooms.find("guestBedroom")->second));
  
  Game::rooms.at("downstairsBathroom")->setExit("Living Room", &(Game::rooms.find("livingRoom")->second));
  
  Game::rooms.at("guestBedroom")->setExit("Living Room", &(Game::rooms.find("livingRoom")->second));
  
  Game::rooms.at("wineCellar")->setExit("Living Room", &(Game::rooms.find("livingRoom")->second));
  
  Game::rooms.at("diningRoom")->setExit("Kitchen", &(Game::rooms.find("kitchen")->second));
  Game::rooms.at("diningRoom")->setExit("Foyer",   &(Game::rooms.find("foyer")->second));

  Game::rooms.at("foyer")->setExit("Kitchen",      &(Game::rooms.find("kitchen")->second));
  Game::rooms.at("foyer")->setExit("Garage",       &(Game::rooms.find("garage")->second));
  Game::rooms.at("foyer")->setExit("Dining Room",  &(Game::rooms.find("diningRoom")->second));
  
  Game::rooms.at("garage")->setExit("Foyer", &(Game::rooms.find("foyer")->second));

  
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

  Game::currentRoom = &(Game::rooms.find("foyer")->second);
}
