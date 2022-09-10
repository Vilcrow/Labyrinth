#include <iostream>
#include "labyrinth.h"
#include "game.h"
#include "commands.h"

Game::Game()
{
    commands = COMMANDS;
    generateMap();
    roomNumber = 1;
}

void Game::run()
{
    std::string input;
    std::shared_ptr<Action> action;
    std::cout << "> ";
    while(std::getline(std::cin, input)) {
        if(!input.empty()) {
            action = commands->cmdToAction(input);
            std::cout << handleAction(*action) << std::endl;
        }
        std::cout << "> ";
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
    LabyrinthObject *object;
    switch(t) {
    case Labyrinth::ObjectWall:
        result = gameMap[roomNumber]->getCurrentWall()->handleAction(act);
        break;
    case Labyrinth::ObjectDoor:
    case Labyrinth::ObjectKey:
        object = gameMap[roomNumber]->getCurrentWall()->findObject(t);
        if(!object)
            result = "Object don't exists.";
        else
            result = object->handleAction(act);
        break;
    default:
        result = "Invalid input.";
    }
    return result;
}
