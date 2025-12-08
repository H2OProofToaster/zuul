#include "commandWords.h"
#include "command.h"
#include "parser.h"
#include "room.h"
#include "inventory.h"
#include <map>
#include <cstring>
#include "game.h"

using namespace std;

/*
  Translated from the implementation of Zuul from Jason Galbraith
  https://drive.google.com/drive/folders/18O6fa2z_WlCBkEIG1eKb8Y57l-PoGaWy
*/

//Global parser and current room pointer
Parser* Game::parser = new Parser();
Room* Game::currentRoom;

//Create the game and intialize its internal map
Game::Game()
{
  Game::createRooms();
  Inventory* inventory = new Inventory();
  winNum = 0;
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
      Command* command = Game::parser->getCommand();
      finished = Game::processCommand(command);
    }
  cout << "Thank you for playing. Good bye.";
}

//Print out the openening message for the player
void Game::printWelcome()
{
  cout << "\nWelcome to Adventure! \n Adventure is a new, incredibly boring adventure game. \nType 'help' if you need help.\n";
  Game::currentRoom->printLongDescription(); //Just couts internally in room.cpp
}


//Given a command, process the command
//If theis command ends the game, true is returned, otherwise false is returned
bool Game::processCommand(Command* command)
{
  bool wantToQuit = false;

  if(command->getCommandWord() == nullptr) { return false; }

  if(command->isUnknown()) { cout << "I don't know what you mean..."; return false; }

  char* commandWord = command->getCommandWord();

  if(strcmp(commandWord, "help") == 0) { Game::printHelp(); }
  else if(strcmp(commandWord, "go") == 0) { Game::goRoom(command); }
  else if(strcmp(commandWord, "inventory") == 0)
    {
      for(int i = 0; i < inventory->getItems().size(); i++) { cout << inventory->getItems()[i]->getName(); }
    }
  else if(strcmp(commandWord, "quit") == 0) { wantToQuit = Game::quitGame(command); }
  else if(strcmp(commandWord, "use") == 0) { Game::useItem(inventory->getItem(command->getSecondWord())); }
  else if(strcmp(commandWord, "drop") == 0)
    {
      if(strcmp(command->getSecondWord(), "") == 0) { cout << "Drop what?"; return wantToQuit; }
      inventory->moveItem(currentRoom->getInventory(), inventory->getItem(command->getSecondWord()));
    }
  else if(strcmp(commandWord, "pickup") == 0)
    {
      if(strcmp(command->getSecondWord(), "") == 0) { cout << "Pickup what?"; return wantToQuit; }
      inventory->moveItem(currentRoom->getInventory(), currentRoom->getItem(command->getSecondWord()));
      cout << inventory->getItem(command->getSecondWord())->getDescription();
    }

  return wantToQuit;
}

//Implementations of user commands

//Uses item if in correct room
void Game::useItem(Item* command)
{
  if(command == NULL) { cout << "Use what?"; return; }

  const char* currentRoomName;
  for(auto& i : this->rooms)
    { if(i.second == currentRoom) { currentRoomName = i.first; } }
  
  if(strcmp(command->getSolutionRoom(), currentRoomName) == 0) //Mmmmmmmmmmmmm loop thru the map
    {
      //Win conditions
      if(strcmp(command->getName(), "Food Note") == 0 and Game::winNum == 3)
	{
	  cout << command->getSolutionText();
	  Game::winNum = 0;
	  return;
	}
      if(strcmp(command->getName(), "Gouda Cheese Bites") == 0 or
	 strcmp(command->getName(), "Brie") == 0 or
	 strcmp(command->getName(), "Popsicles") == 0)
	{
	  Game::winNum += 1;
	}

      cout << command->getSolutionText();
      Game::inventory->removeItem(command->getName());
    }
  else { cout << "You can't use that here"; }
}

//Print out some help information, here we print some stupid cryptic message and a list of all the command
void Game::printHelp()
{
  cout << "You are lost. You are alone. You wander around the school. \nYour command words are:";
  Game::parser->showCommands();
}

//Try to go one directions, if there is an exit, enter the new room, otherwise print an error message
void Game::goRoom(Command* command)
{
  //If there is no second word, we don't know where to go
  if(!command->hasSecondWord()) { cout << "Go where?"; return; }

  Room* nextRoom = currentRoom->getExit(command->getSecondWord());

  //Try to leave current room
  if(nextRoom == NULL) { cout << "There is no door!"; }
  else
  {
    currentRoom = nextRoom;
    currentRoom->printLongDescription(); //Just couts internally in room.cpp

    //Prints out items in room, if any
    if(!currentRoom->getItems().empty()) { cout << "There are items: "; }
    for(int i = 0; i < currentRoom->getItems().size(); i++) { cout << currentRoom->getItems()[i]->getName() << ", "; }
  }
}

//"Quit" was entered, check the rest fo the command we really quit the game
//Return true, if this command quits the game, false otherwise
bool Game::quitGame(Command* command)
{
  if(command->hasSecondWord()) { cout << "Quit what?"; return false; }
  else { return true; }
}

//Create all the rooms and link their exits together
void Game::createRooms()
{
  //Create the rooms, help from ChatGPT saying const char pointers are better and formatting all of it. 5/12/25

  //Key consts
  const char* MYROOM            = "myRoom";
  const char* HALLWAY           = "hallway";
  const char* SISTERROOM        = "sisterRoom";
  const char* PARENTROOM        = "parentRoom";
  const char* PARENTBATHROOM    = "parentBathroom";
  const char* PARENTCLOSET      = "parentCloset";
  const char* LAUNDRYROOM       = "laundryRoom";
  const char* WATERHEATERROOM   = "waterHeaterRoom";
  const char* UPBATHROOM        = "upstairsBathroom";
  const char* OFFICE            = "office";
  const char* BONUSROOM         = "bonusRoom";
  const char* KITCHEN           = "kitchen";
  const char* LIVINGROOM        = "livingRoom";
  const char* DOWNBATHROOM      = "downstairsBathroom";
  const char* GUESTBEDROOM      = "guestBedroom";
  const char* FOYER             = "foyer";
  const char* DININGROOM        = "diningRoom";
  const char* GARAGE            = "garage";
  const char* WINECELLAR        = "wineCellar";

  //Make rooms
  this->rooms[MYROOM]          = new Room("where I sleep");
  this->rooms[HALLWAY]         = new Room("where it's a hallway");
  this->rooms[SISTERROOM]      = new Room("where it's pink");
  this->rooms[PARENTROOM]      = new Room("where my parents sleep");
  this->rooms[PARENTBATHROOM]  = new Room("where my parents bathe");
  this->rooms[PARENTCLOSET]    = new Room("where it's a closet");
  this->rooms[LAUNDRYROOM]     = new Room("where it has a big sink");
  this->rooms[WATERHEATERROOM] = new Room("where it's kinda scary here");
  this->rooms[UPBATHROOM]      = new Room("where my sister's side is messy");
  this->rooms[OFFICE]          = new Room("where it's not my office");
  this->rooms[BONUSROOM]       = new Room("where it gets hot in here");
  this->rooms[KITCHEN]         = new Room("where it's food");
  this->rooms[LIVINGROOM]      = new Room("where we live");
  this->rooms[DOWNBATHROOM]    = new Room("where I use it sometimes");
  this->rooms[GUESTBEDROOM]    = new Room("where I don't use it sometimes");
  this->rooms[FOYER]           = new Room("in the foyer I guess");
  this->rooms[DININGROOM]      = new Room("eat here");
  this->rooms[GARAGE]          = new Room("where the popsicles are");
  this->rooms[WINECELLAR]      = new Room("... well, what do you think is here");
  
  //Set exits
  this->rooms[MYROOM]->setExit("Hallway", this->rooms[HALLWAY]);

  this->rooms[HALLWAY]->setExit("My Room", this->rooms[MYROOM]);
  this->rooms[HALLWAY]->setExit("Sister's Room", this->rooms[SISTERROOM]);
  this->rooms[HALLWAY]->setExit("Parent's Room", this->rooms[PARENTROOM]);
  this->rooms[HALLWAY]->setExit("Laundry Room", this->rooms[LAUNDRYROOM]);
  this->rooms[HALLWAY]->setExit("Upstairs Bathroom", this->rooms[UPBATHROOM]);
  this->rooms[HALLWAY]->setExit("Office", this->rooms[OFFICE]);
  this->rooms[HALLWAY]->setExit("Bonus Room", this->rooms[BONUSROOM]);
  this->rooms[HALLWAY]->setExit("Kitchen", this->rooms[KITCHEN]);

  this->rooms[SISTERROOM]->setExit("Hallway", this->rooms[HALLWAY]);

  this->rooms[PARENTROOM]->setExit("Hallway", this->rooms[HALLWAY]);
  this->rooms[PARENTROOM]->setExit("Parent's Bathroom", this->rooms[PARENTBATHROOM]);

  this->rooms[PARENTBATHROOM]->setExit("Parent's Room", this->rooms[PARENTROOM]);
  this->rooms[PARENTBATHROOM]->setExit("Parent's Closet", this->rooms[PARENTCLOSET]);

  this->rooms[PARENTCLOSET]->setExit("Parent's Bathroom", this->rooms[PARENTBATHROOM]);
  
  this->rooms[LAUNDRYROOM]->setExit("Hallway", this->rooms[HALLWAY]);
  this->rooms[LAUNDRYROOM]->setExit("Water Heater Room", this->rooms[WATERHEATERROOM]);
  
  this->rooms[WATERHEATERROOM]->setExit("Laundry Room", this->rooms[LAUNDRYROOM]);
  
  this->rooms[UPBATHROOM]->setExit("Hallway", this->rooms[HALLWAY]);
  
  this->rooms[OFFICE]->setExit("Hallway", this->rooms[HALLWAY]);
  
  this->rooms[BONUSROOM]->setExit("Hallway", this->rooms[HALLWAY]);
  
  this->rooms[KITCHEN]->setExit("Hallway", this->rooms[HALLWAY]);
  this->rooms[KITCHEN]->setExit("Living Room", this->rooms[LIVINGROOM]);
  this->rooms[KITCHEN]->setExit("Dining Room", this->rooms[DININGROOM]);
  this->rooms[KITCHEN]->setExit("Foyer", this->rooms[FOYER]);

  this->rooms[LIVINGROOM]->setExit("Kitchen", this->rooms[KITCHEN]);
  this->rooms[LIVINGROOM]->setExit("Wine Cellar", this->rooms[WINECELLAR]);
  this->rooms[LIVINGROOM]->setExit("Downstairs Bathroom", this->rooms[DOWNBATHROOM]);
  this->rooms[LIVINGROOM]->setExit("Guest Bedroom", this->rooms[GUESTBEDROOM]);
  
  this->rooms[DOWNBATHROOM]->setExit("Living Room", this->rooms[LIVINGROOM]);
  
  this->rooms[GUESTBEDROOM]->setExit("Living Room", this->rooms[LIVINGROOM]);
  
  this->rooms[WINECELLAR]->setExit("Living Room", this->rooms[LIVINGROOM]);
  
  this->rooms[DININGROOM]->setExit("Kitchen", this->rooms[KITCHEN]);
  this->rooms[DININGROOM]->setExit("Foyer", this->rooms[FOYER]);
  
  this->rooms[FOYER]->setExit("Kitchen", this->rooms[KITCHEN]);
  this->rooms[FOYER]->setExit("Garage", this->rooms[GARAGE]);
  this->rooms[FOYER]->setExit("Dining Room", this->rooms[DININGROOM]);
  
  this->rooms[GARAGE]->setExit("Foyer", this->rooms[FOYER]);

  //Add Items
  this->rooms.at("myRoom")->addItem("Food Note",
				   "You need to get some food:\n1. Gouda Cheese Bites\n2. Brie\n3. Popsicles\nAnd return to your room.",
				   "myRoom",
				   "You have successfully gathered the snacks!\nYou win!");
  this->rooms.at("hallway")->addItem("Kamala Harris",
				    "A cardboard standee of Kamala Harris.\nAdorned with a rainbow inflatable crown, green gummy bear chains, and a hawaiian shirt.",
				    "None",
				    "None");
  this->rooms.at("garage")->addItem("Popsicles",
				    "They are of flavor pineapple.",
				    "myRoom",
				    "That was delicious.");
  this->rooms.at("kitchen")->addItem("Gouda Chese Bites",
				     "There must be something other than cheese in this, I'm addicted.",
				     "myRoom",
				     "That was delicious.");
  this->rooms.at("kitchen")->addItem("Brie",
				     "A very good melting cheese, enjoy with bread.",
				     "myRoom",
				     "That was delicious.");

  Game::currentRoom = this->rooms[FOYER];
}
