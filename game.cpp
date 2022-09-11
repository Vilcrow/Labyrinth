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
    LabyrinthObject *object;
    switch(act.oType) {
    case Labyrinth::ObjectBackpack:
        result = backpack->handleAction(act);
        break;
    case Labyrinth::ObjectWall:
        result = gameMap[roomNumber]->getCurrentWall()->handleAction(act);
        break;
    case Labyrinth::ObjectDoor:
    case Labyrinth::ObjectKey:
        object = gameMap[roomNumber]->getCurrentWall()->findObject(act.oType);
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
