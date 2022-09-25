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
            if(action.aType == Labyrinth::ActionSave) {
                save();
                continue;
            }
            else if(action.aType == Labyrinth::ActionQuit) {
                break;
            }
            else {
                std::cout << "Invalid input." << std::endl;
                std::cout << "> ";
                continue;
            }
        }
        if(action.oType == Labyrinth::ObjectBackpack) {
            curContainer = backpack;
            result = ActionWithBackpack(action.aType);
        }
        else if(action.oType == Labyrinth::ObjectRoom)
            result = ActionWithRoom(action.aType, gameMap[roomNumber]);
        else if(action.oType == Labyrinth::ObjectWall) {
            curContainer = gameMap[roomNumber]->getCurrentWall();
            result = ActionWithWall(action.aType);
        }
        else if(action.oType == Labyrinth::ObjectWallTop   ||
                action.oType == Labyrinth::ObjectWallDown  ||
                action.oType == Labyrinth::ObjectWallLeft  ||
                action.oType == Labyrinth::ObjectWallRight) {
            Labyrinth::WallType wType = WallContainer::getWallType(action.oType);
            if(wType != Labyrinth::WallNone) {
                gameMap[roomNumber]->setCurrentWall(wType);
                curContainer = gameMap[roomNumber]->getCurrentWall();
                result = ActionWithWall(action.aType);
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
        COMMANDS->addCommand(input);
        std::cout << result << std::endl;
        std::cout << "> ";
    }
}

void Game::generateMap()
{
    int roomsCount = 81;
    for(int i = 1; i <= roomsCount; i++) {
        gameMap[i] = new RoomObject(i);
    }
    DoorObject *door = nullptr;
    KeyObject *key = nullptr;
    InscriptionObject *inscription = nullptr;
    //ROOM 1
    //wall TOP
    door = new DoorObject(2, false);
    gameMap[1]->addObject(Labyrinth::WallTop, door);
    inscription = new InscriptionObject("Qui quaerit, reperit.");
    gameMap[1]->addObject(Labyrinth::WallTop, inscription);
    //wall LEFT
    door = new DoorObject(4, false);
    gameMap[1]->addObject(Labyrinth::WallLeft, door);
    //wall DOWN
    door = new DoorObject(6, false);
    gameMap[1]->addObject(Labyrinth::WallDown, door);
    key = new KeyObject(13);
    gameMap[1]->addObject(Labyrinth::WallDown, key);
    key = new KeyObject(2);
    gameMap[1]->addObject(Labyrinth::WallDown, key);
    //wall RIGHT
    door = new DoorObject(8, false);
    gameMap[1]->addObject(Labyrinth::WallRight, door);
    //ROOM 2
    //wall TOP
    //wall LEFT
    //wall DOWN
    door = new DoorObject(1, false);
    gameMap[2]->addObject(Labyrinth::WallDown, door);
    //wall RIGHT
    door = new DoorObject(9);
    gameMap[2]->addObject(Labyrinth::WallRight, door);
    //ROOM 3
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 4
    //wall TOP
    //wall LEFT
    door = new DoorObject(15, false);
    gameMap[4]->addObject(Labyrinth::WallLeft, door);
    //wall DOWN
    key = new KeyObject(9);
    gameMap[4]->addObject(Labyrinth::WallDown, key);
    //wall RIGHT
    door = new DoorObject(1, false);
    gameMap[4]->addObject(Labyrinth::WallRight, door);
    //ROOM 5
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 6
    //wall TOP
    door = new DoorObject(1, false);
    gameMap[6]->addObject(Labyrinth::WallTop, door);
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 7
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 8
    //wall TOP
    //wall LEFT
    door = new DoorObject(1, false);
    gameMap[8]->addObject(Labyrinth::WallLeft, door);
    //wall DOWN
    //wall RIGHT
    //ROOM 9
    //wall TOP
    //wall LEFT
    door = new DoorObject(2, false);
    gameMap[9]->addObject(Labyrinth::WallLeft, door);
    //wall DOWN
    //wall RIGHT
    //ROOM 10
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 11
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 12
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 14
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 15
    //wall TOP
    //wall LEFT
    door = new DoorObject(34, false);
    gameMap[15]->addObject(Labyrinth::WallLeft, door);
    //wall DOWN
    //wall RIGHT
    door = new DoorObject(4, false);
    gameMap[15]->addObject(Labyrinth::WallRight, door);
    //ROOM 16
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 17
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 18
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 19
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 20
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 21
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 22
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 23
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 24
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 25
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 26
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 27
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 28
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 29
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 30
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 31
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 32
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 33
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 34
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    door = new DoorObject(15, false);
    gameMap[34]->addObject(Labyrinth::WallRight, door);
    //ROOM 35
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 36
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 37
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 38
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 39
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 40
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 41
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 42
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 43
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 44
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 45
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 46
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 47
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 48
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 49
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 50
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 51
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 52
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 53
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 54
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 55
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 56
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 57
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 58
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 59
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 60
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 61
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 62
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 63
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 64
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 65
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 66
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 67
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 68
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 69
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 70
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 71
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 72
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 73
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 74
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 75
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 76
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 77
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 78
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 79
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 80
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 81
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
}

std::string Game::handleAction(Action act, LabyrinthObject *obj)
{
    if(!obj)
        return "Error. Invalid pointer for the object.";
    std::string result = "Invalid input.";
    switch(act.oType) {
    case Labyrinth::ObjectBattery:
        result = ActionWithBattery(act.aType, static_cast<BatteryObject*>(obj));
        break;
    case Labyrinth::ObjectDoor:
        result = ActionWithDoor(act.aType, static_cast<DoorObject*>(obj));
        break;
    case Labyrinth::ObjectInscription:
        result = ActionWithInscription(act.aType,
                                       static_cast<InscriptionObject*>(obj));
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
    case Labyrinth::ObjectWatch:
        result = ActionWithWatch(act.aType, static_cast<WatchObject*>(obj));
        break;
//no processing required
    case Labyrinth::ObjectNone:
    case Labyrinth::ObjectBackpack:
    case Labyrinth::ObjectWall:
    case Labyrinth::ObjectWallDown:
    case Labyrinth::ObjectWallLeft:
    case Labyrinth::ObjectWallRight:
    case Labyrinth::ObjectWallTop:
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

std::string Game::ActionWithBattery(Labyrinth::ActionType aType,
                                    BatteryObject *battery)
{
    std::string result;
    switch(aType) {
    case Labyrinth::ActionInspect:
        result = "Charge is " + battery->getCharge();
    case Labyrinth::ActionTake:
        if(backpack->getCapacity() == 0)
            result = "The backpack is full.";
        else if(gameMap[roomNumber]->getCurrentWall()->removeObject(battery)) {
            backpack->addObject(battery);
            result = "The battery taked";
        }
        else {
            result = "No such item.";
        }
        break;
    case Labyrinth::ActionThrow:
        if(backpack->removeObject(battery)) {
            gameMap[roomNumber]->getCurrentWall()->addObject(battery);
            result = "The battery throwed.";
        }
        else {
            result = "No such item.";
        }
        break;
    default:
        result = "Impossible action with the battery.";
    }
    return result;
}

std::string Game::ActionWithDoor(Labyrinth::ActionType aType, DoorObject *door)
{
    std::string result;
    switch(aType) {
    case Labyrinth::ActionClose:
        result = "There's no need.";
        break;
    case Labyrinth::ActionEnter:
        if(door->isLocked()) {
            result = "The door is locked. We need to open it.";
        }
        else {
            int prev_room = roomNumber;
            DoorObject *back_door;
            roomNumber = door->getNumber();
            //open the return door in current room
            back_door = gameMap[roomNumber]->findDoor(prev_room);
            if(back_door)
                back_door->setLocked(false);
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
            LabyrinthObject *key = backpack->findKey(door->getNumber());
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
        result = "Impossible action with the door.";
    }
    return result;
}

std::string Game::ActionWithInscription(Labyrinth::ActionType aType,
                                        InscriptionObject *inscription)
{
    std::string result;
    switch(aType) {
    case Labyrinth::ActionRead:
    case Labyrinth::ActionInspect:
        result = "\"" + inscription->getInscription() + "\"";
        break;
    default:
        result = "Impossible action with the inscription.";
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
        result = "Impossible action with the key.";
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
            result = "The sheet taked";
        }
        else {
            result = "No such item.";
        }
        break;
    case Labyrinth::ActionThrow:
        if(backpack->removeObject(sheet)) {
            gameMap[roomNumber]->getCurrentWall()->addObject(sheet);
            result = "The sheet throwed.";
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

std::string Game::ActionWithWall(Labyrinth::ActionType aType)
{
    std::string result;
    switch(aType) {
    case Labyrinth::ActionInspect:
        result = "You see: ";
        result += Commands::objectsList(
                  static_cast<WallContainer*>(curContainer)->getObjects());
        break;
    default:
        result = "Impossible. You can just inspect the wall.";
    }
    return result;
}
std::string Game::ActionWithWatch(Labyrinth::ActionType aType,
                                  WatchObject *watch)
{
    std::string result;
    switch(aType) {
    case Labyrinth::ActionInspect:
        result = "Time is " + watch->getTime();
    case Labyrinth::ActionTake:
        if(backpack->getCapacity() == 0)
            result = "The backpack is full.";
        else if(gameMap[roomNumber]->getCurrentWall()->removeObject(watch)) {
            backpack->addObject(watch);
            result = "The watch taked";
        }
        else {
            result = "No such item.";
        }
        break;
    case Labyrinth::ActionThrow:
        if(backpack->removeObject(watch)) {
            gameMap[roomNumber]->getCurrentWall()->addObject(watch);
            result = "Watch throwed.";
        }
        else {
            result = "No such item.";
        }
        break;
    default:
        result = "Impossible action with the watch.";
    }
    return result;
}

bool Game::save()
{
    return true;
}
