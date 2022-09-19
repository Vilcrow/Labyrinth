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

Game::Game()
{
    backpack = new BackpackContainer();
    generateMap();
    roomNumber = 1;
    curContainer = gameMap[roomNumber]->getCurrentWall();
}

void Game::run()
{
    std::string input, result;
    std::cout << "> ";
    while(std::getline(std::cin, input)) {
        if(input.empty()) {
            std::cout << "> ";
            continue;
        }
        Action action = COMMANDS->cmdToAction(input);
        if(action.aType == Labyrinth::ActionNone ||
           (action.oType == Labyrinth::ObjectNone && action.number == -1)) {
            std::cout << "Invalid input.";
            std::cout << "> ";
            continue;
        }
        if(action.oType == Labyrinth::ObjectBackpack) {
            curContainer = backpack;
            result = ActionWithBackpack(action.aType);
        }
        else if(action.oType == Labyrinth::ObjectRoom)
            result = ActionWithRoom(action.aType, gameMap[roomNumber]);
        else if(action.oType == Labyrinth::ObjectWall) {
            curContainer = gameMap[roomNumber]->getCurrentWall();
            result = ActionWithWall(action.aType,
                                    static_cast<WallContainer*>(curContainer));
        }
        else if(action.oType == Labyrinth::ObjectWallTop   ||
                action.oType == Labyrinth::ObjectWallDown  ||
                action.oType == Labyrinth::ObjectWallLeft  ||
                action.oType == Labyrinth::ObjectWallRight) {
            Labyrinth::WallType wType = WallContainer::getWallType(action.oType);
            if(wType != Labyrinth::WallNone) {
                gameMap[roomNumber]->setCurrentWall(wType);
                curContainer = gameMap[roomNumber]->getCurrentWall();
                result = ActionWithWall(action.aType,
                                        static_cast<WallContainer*>(curContainer));
            }
        }
        else {
            LabyrinthObject *object = curContainer->findObject(action);
            if(!object) {
                result = "No such item ";
                if(curContainer == backpack)
                    result += "in backpack.";
                else
                    result += "on this side.";
            }
            else {
                action.oType = object->getType();
                result = handleAction(action, object);
            }
        }
        std::cout << result << std::endl;
        std::cout << "> ";
    }
}

void Game::generateMap()
{
    int roomsCount = 81;
    for(int i = 1; i <= roomsCount; i++) {
        gameMap[i] = new RoomObject(1);
    }
    DoorObject *door = nullptr;
    KeyObject *key = nullptr;
    //->room #1
    //---->top wall
    door = new DoorObject(2, false);
    gameMap[1]->addObject(Labyrinth::WallTop, door);
    //---->left wall
    door = new DoorObject(4, false);
    gameMap[1]->addObject(Labyrinth::WallLeft, door);
    //---->down wall
    door = new DoorObject(6, false);
    gameMap[1]->addObject(Labyrinth::WallDown, door);
    key = new KeyObject(13);
    gameMap[1]->addObject(Labyrinth::WallDown, key);
    //---->right wall
    door = new DoorObject(8, false);
    gameMap[1]->addObject(Labyrinth::WallRight, door);
    //->room #2
    //---->top wall
    //---->left wall
    //---->down wall
    door = new DoorObject(1, false);
    gameMap[2]->addObject(Labyrinth::WallDown, door);
    //---->right wall
    //->room #3
    //---->top wall
    //---->left wall
    //---->down wall
    //---->right wall
    //->room #4
    //---->top wall
    //---->left wall
    //---->down wall
    //---->right wall
    door = new DoorObject(1, false);
    gameMap[4]->addObject(Labyrinth::WallRight, door);
    //->room #5
    //---->top wall
    //---->left wall
    //---->down wall
    //---->right wall
    //->room #6
    //---->top wall
    door = new DoorObject(1, false);
    gameMap[6]->addObject(Labyrinth::WallTop, door);
    //---->left wall
    //---->down wall
    //---->right wall
    //->room #7
    //---->top wall
    //---->left wall
    //---->down wall
    //---->right wall
    //->room #8
    //---->top wall
    //---->left wall
    door = new DoorObject(1, false);
    gameMap[8]->addObject(Labyrinth::WallLeft, door);
    //---->down wall
    //---->right wall
}

std::string Game::handleAction(Action act, LabyrinthObject *obj)
{
    if(!obj)
        return "Error. Invalid pointer for the object.";
    std::string result = "Invalid input.";
    switch(act.oType) {
    case Labyrinth::ObjectBattery:
      //result = ActionWithBattery(act.aType, static_cast<BatteryObject*>(obj));
        break;
    case Labyrinth::ObjectDoor:
        result = ActionWithDoor(act.aType, static_cast<DoorObject*>(obj));
        break;
    case Labyrinth::ObjectFlashlight:
        break;
    case Labyrinth::ObjectKey:
        result = ActionWithKey(act.aType, static_cast<KeyObject*>(obj));
        break;
    case Labyrinth::ObjectRoom:
        result = ActionWithRoom(act.aType, gameMap[roomNumber]);
        break;
    case Labyrinth::ObjectSheet:
        result = ActionWithSheet(act.aType, static_cast<SheetObject*>(obj));
        break;
//no processing required
    case Labyrinth::ObjectNone:
    case Labyrinth::ObjectBackpack:
    case Labyrinth::ObjectWall:
    case Labyrinth::ObjectWallTop:
    case Labyrinth::ObjectWallDown:
    case Labyrinth::ObjectWallLeft:
    case Labyrinth::ObjectWallRight:
        break;
    }
    return result;
}

std::string Game::ActionWithBackpack(Labyrinth::ActionType aType)
{
    std::string result;
    switch(aType) {
    case Labyrinth::ActionInspect:
        result = "In backpack: ";
        result += Commands::objectsList(backpack->getObjects());
        result += " Capacity is " + std::to_string(backpack->getCapacity())
                                  + ".";
        break;
    default:
        result = "Impossible action with the backpack.";
    }
    return result;
}

/*
std::string Game::ActionWithBattery(Labyrinth::ActionType aType,
                                    BatteryObject *battery)
{

}
*/
std::string Game::ActionWithDoor(const Action& act, DoorObject *door)
{
    std::string result;
    switch(act.aType) {
    case Labyrinth::ActionClose:    //maybe need fix
        result = "There's no need.";
        break;
    case Labyrinth::ActionEnter:
        if(door->isLocked()) {
            result = "The door is locked. We need to open it.";
        }
        else {
            int prevRoom = roomNumber;
            DoorObject *backDoor;
            roomNumber = door->getNumber();
            //open the return door in current room
            backDoor = gameMap[roomNumber]->findDoor(prevRoom);
            if(backDoor)
                backDoor->setLocked(false);
            curContainer = gameMap[roomNumber]->getCurrentWall();
            result = "You entered room ";
            result += std::to_string(roomNumber);
            result += ".";
        }
        break;
    case Labyrinth::ActionOpen:
        if(!door->isLocked())
            result = "Door already opened.";
        else {
            LabyrinthObject *key = backpack->findObject(act);
            if(!key)
                result = "The door is locked. Need a suitable key.";
            else if(static_cast<KeyObject*>(key)->getNumber() != door->getNumber())
                result = "The key doesn't fit.";
            else {
                door->setLocked(false);
                backpack->removeObject(key); //the key is no longer needed
                result = "You open the door.";
            }
        }
        break;
    case Labyrinth::ActionInspect:
        result = "You see door with number ";
        result += std::to_string(door->getNumber()) + ".";
        break;
    default:
        result = "Impossible action with the door";
    }
    return result;
}

std::string Game::ActionWithKey(Labyrinth::ActionType aType, KeyObject *key)
{
    std::string result;
    switch(aType) {
    case Labyrinth::ActionInspect:
        result = "Key with number ";
        result += std::to_string(key->getNumber()) + ".";
        break;
    case Labyrinth::ActionTake:
        if(backpack->getCapacity() == 0)
            result = "The backpack is full.";
        else if(gameMap[roomNumber]->getCurrentWall()->removeObject(key)) {
            backpack->addObject(key);
            result = "Taked.";
        }
        else {
            result = "No such item.";
        }
        break;
    case Labyrinth::ActionThrow:
        if(backpack->removeObject(key)) {
            gameMap[roomNumber]->getCurrentWall()->addObject(key);
            result = "Done.";
        }
        else {
            result = "No such item.";
        }
        break;
    default:
        result = "Impossible action with the key";
    }
    return result;

}

std::string Game::ActionWithRoom(Labyrinth::ActionType aType, RoomObject *room)
{
    std::string result;
    switch(aType) {
    case Labyrinth::ActionInspect:
        result = "Room number ";
        result += std::to_string(room->getNumber());
        result += '.';
        break;
    default:
        result = "Impossible. You can just inspect the room.";
    }
    return result;
}

std::string Game::ActionWithSheet(Labyrinth::ActionType aType, SheetObject *sheet)
{
    std::string result;
    switch(aType) {
    case Labyrinth::ActionInspect:
        result = "Record: ";
        result += sheet->getRecord();
        break;
    case Labyrinth::ActionTake:
        if(backpack->getCapacity() == 0)
            result = "The backpack is full.";
        else if(gameMap[roomNumber]->getCurrentWall()->removeObject(sheet)) {
            backpack->addObject(sheet);
            result = "Sheet taked";
        }
        else {
            result = "No such item.";
        }
        break;
    case Labyrinth::ActionThrow:
        if(backpack->removeObject(sheet)) {
            gameMap[roomNumber]->getCurrentWall()->addObject(sheet);
            result = "Sheet throwed.";
        }
        else {
            result = "No such item.";
        }
        break;
    default:
        result = "Impossible action with the sheet.";
    }
    return result;
}

std::string Game::ActionWithWall(Labyrinth::ActionType aType,
                                 WallContainer *wall)
{
    std::string result;
    switch(aType) {
    case Labyrinth::ActionInspect:
        result = "You see: ";
        result += Commands::objectsList(wall->getObjects());
        break;
    default:
        result = "Impossible. You can just inspect the wall.";
    }
    return result;
}
