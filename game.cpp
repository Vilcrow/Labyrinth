#include <iostream>
#include "labyrinth.h"
#include "game.h"
#include "commands.h"

Game* Game::uniqueInstance = nullptr;

Game::Game()
{
    Commands *commands = Commands::instance();
    generateMap();
    roomNumber = 1;
}

Game* Game::instance()
{
    if(!uniqueInstance)
        uniqueInstance = new Game();
    return uniqueInstance;
}

void Game::run()
{
    std::string input;
    std::shared_ptr<Action> action;
    while(std::getline(std::cin, input)) {
        action = commands->cmdToAction(input);
        std::cout << handleAction(*action) << std::endl;
    }
}

void Game::generateMap()
{
    //draft
    RoomObject *room = new RoomObject();
    KeyObject *key = new KeyObject(2);
    DoorObject *door = new DoorObject(2);
    room->addObject(Labyrinth::WallTop, key);
    room->addObject(Labyrinth::WallTop, door);
    gameMap[1] = room;
}

std::string Game::handleAction(const Action& act)
{
    std::string result;
    Labyrinth::ObjectType t = act.oType;
    switch(t) {
    case Labyrinth::ObjectWall:
        result = gameMap[roomNumber]->getCurrentWall()->handleAction(act);
        break;
    default:
        result = "Impossible";
    }
    return result;
}
