/*******************************************************************************
** vim:ts=4:sw=4:expandtab
**
** This file is part of the labyrinth project, a text adventure game
**
** Copyright (C) 2022 S.V.I 'Vilcrow', <vilcrow.net>
**
** LICENCE:
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
**
*******************************************************************************/

#include <iostream>
#include "labyrinth.h"
#include "game.h"
#include "commands.h"

Game::Game()
{
    backpack = new BackpackContainer();
    generateMap();
    roomNumber = 1;
    curContainer = gameMap[roomNumber]->getCurrentWall();
}

void Game::run()
{
    std::string input;
    std::shared_ptr<Action> action;
    std::cout << "> ";
    while(std::getline(std::cin, input)) {
        if(!input.empty()) {
            action = COMMANDS->cmdToAction(input);
            action->wall = gameMap[roomNumber]->getCurrentWall();
            action->backpack = backpack;
            std::cout << handleAction(*action) << std::endl;
        }
        std::cout << "> ";
    }
}

void Game::generateMap()
{
    //draft
    RoomObject *room = new RoomObject(1);
    KeyObject *key = new KeyObject(2);
    DoorObject *door = new DoorObject(2);
    room->addObject(Labyrinth::WallTop, key);
    room->addObject(Labyrinth::WallTop, door);
    gameMap[room->getNumber()] = room;
}

std::string Game::handleAction(Action& act)
{
    std::string result;
    LabyrinthObject *object;
    Labyrinth::WallType wType;
    switch(act.oType) {
    case Labyrinth::ObjectRoom:
        result = gameMap[roomNumber]->handleAction(act);
        break;
    case Labyrinth::ObjectBackpack:
        curContainer = backpack;
        result = curContainer->handleAction(act);
        break;
    case Labyrinth::ObjectWall:
        curContainer = gameMap[roomNumber]->getCurrentWall();
        result = curContainer->handleAction(act);
        break;
    case Labyrinth::ObjectWallTop:
    case Labyrinth::ObjectWallDown:
    case Labyrinth::ObjectWallLeft:
    case Labyrinth::ObjectWallRight:
        wType = WallContainer::getWallType(act.oType);
        if(wType == Labyrinth::WallNone)
            break;
        gameMap[roomNumber]->setCurrentWall(wType);
        curContainer = gameMap[roomNumber]->getCurrentWall();
        result = curContainer->handleAction(act);
        break;
    case Labyrinth::ObjectDoor:
    case Labyrinth::ObjectKey:
        object = curContainer->findObject(act.oType);
        if(!object) {
            result = "No such item ";
            if(curContainer == backpack)
                result += "in backpack.";
            else
                result += "on this side.";
        }
        else
            result = object->handleAction(act);
        break;
    default:
        result = "Invalid input.";
    }
    return result;
}
