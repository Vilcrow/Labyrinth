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

#include "labyrinth.h"
#include "game.h"
#include "keylock.h"
#include <iostream>

Game::Game()
{
    roomNumber = 1;
    curWallType = Lbr::WallTop;
    backpack = new Backpack();
    generateMap();
    curContainer = nullptr;
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
        if(action.aType == Lbr::ActNone ||
           (action.oName == Lbr::ObjNone && action.number == -1)) {
            if(action.aType == Lbr::ActSave) {
                save();
                continue;
            }
            else if(action.aType == Lbr::ActQuit) {
                break;
            }
            else {
                std::cout << "Invalid input." << std::endl;
                std::cout << "> ";
                continue;
            }
        }
        if(action.oName == Lbr::ObjBackpack) {
            curContainer = backpack;
            result = ActionWithBackpack(action.aType);
        }
        else if(action.oName == Lbr::ObjRoom) {
            curContainer = nullptr;
            result = ActionWithRoom(action.aType, gameMap[roomNumber]);
        }
        else if(action.oName == Lbr::ObjWall)
            result = ActionWithWall(action.aType);
        else if(action.oName == Lbr::ObjWallTop   ||
                action.oName == Lbr::ObjWallDown  ||
                action.oName == Lbr::ObjWallLeft  ||
                action.oName == Lbr::ObjWallRight) {
            curWallType = Wall::getWallType(action.oName);
            result = ActionWithWall(action.aType);
        }
        else {
            if(action.oType == Lbr::Object) {
                LbrObject *object = curContainer->findObject(action);
                if(!object)
                    result = "No such item ";
                else {
                    action.oName = object->getName();
                    result = handleActionWithObject(action, object);
                }
            }
            else if(action.oType == Lbr::Container) {
                Wall *curWall = gameMap[roomNumber]->getWall(curWallType);
                curContainer = curWall->findContainer(action);
                if(!curContainer)
                    result = "No such item ";
                else {
                    action.oName = curContainer->getName();
                    result = handleActionWithContainer(action);
                }
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
        gameMap[i] = new Room(i);
    }
    Door *door = nullptr;
    KeyLock *keylock = nullptr;
    Key *key = nullptr;
    Shelf *shelf = nullptr;
    //ROOM 1
    //wall TOP
    door = new Door(2);
    keylock = new KeyLock(2);
    door->addLock(keylock);
    gameMap[1]->addContainer(Lbr::WallTop, door);
    shelf = new Shelf();
    key = new Key(2);
    shelf->addObject(key);
    gameMap[1]->addContainer(Lbr::WallLeft, shelf);
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 2
    //wall TOP
    //wall LEFT
    //wall DOWN
    door = new Door(1);
    keylock = new KeyLock(1);
    door->addLock(keylock);
    gameMap[2]->addContainer(Lbr::WallDown, door);
    //wall RIGHT
}

std::string Game::handleActionWithObject(Action act, LbrObject *obj)
{
    if(!obj)
        return "Error. Invalid pointer for the object.";
    std::string result = "Invalid input.";
    switch(act.oName) {
    case Lbr::ObjBattery:
        result = ActionWithBattery(act.aType, static_cast<Battery*>(obj));
        break;
    case Lbr::ObjInscription:
        result = ActionWithInscription(act.aType,
                                       static_cast<Inscription*>(obj));
        break;
    case Lbr::ObjKey:
        result = ActionWithKey(act.aType, static_cast<Key*>(obj));
        break;
    case Lbr::ObjRoom:
        result = ActionWithRoom(act.aType, gameMap[roomNumber]);
        break;
    case Lbr::ObjSheet:
        result = ActionWithSheet(act.aType, static_cast<Sheet*>(obj));
        break;
    case Lbr::ObjWatch:
        result = ActionWithWatch(act.aType, static_cast<Watch*>(obj));
        break;
//no processing required
    case Lbr::ObjNone:
    case Lbr::ObjBackpack:
    case Lbr::ObjWall:
    case Lbr::ObjWallDown:
    case Lbr::ObjWallLeft:
    case Lbr::ObjWallRight:
    case Lbr::ObjWallTop:
        break;
    }
    return result;
}

std::string Game::handleActionWithContainer(Action act)
{
    std::string result;
    switch(act.oName) {
    case Lbr::ObjDoor:
        result = ActionWithDoor(act.aType);
        break;
    case Lbr::ObjShelf:
        result = ActionWithShelf(act.aType);
        break;
    default:
        result = "Default result.";
    }
    return result;
}

std::string Game::ActionWithBackpack(Lbr::ActType aType)
{
    std::string result;
    switch(aType) {
    case Lbr::ActInspect:
        result = "In backpack: ";
        result += LbrObjectsList<LbrObject>(backpack->getObjects());
        break;
    default:
        result = "Impossible action with the backpack.";
    }
    return result;
}

std::string Game::ActionWithBattery(Lbr::ActType aType, Battery *battery)
{
    std::string result;
    switch(aType) {
    case Lbr::ActInspect:
        result = "Charge is " + battery->getCharge();
    case Lbr::ActTake:
        break;
    case Lbr::ActThrow:
        break;
    default:
        result = "Impossible action with the battery.";
    }
    return result;
}

std::string Game::ActionWithDoor(Lbr::ActType aType)
{
    Door *door = static_cast<Door*>(curContainer);
    std::string result;
    switch(aType) {
    case Lbr::ActClose:
        result = "There's no need.";
        break;
    case Lbr::ActEnter:
        if(door->isLocked()) {
            result = "The door is locked. We need to open it.";
        }
        else {
            int prev_room = roomNumber;
            Door *back_door;
            roomNumber = door->getNumber();
            //open the return door in current room
            back_door = gameMap[roomNumber]->findDoor(prev_room);
            if(back_door)
                back_door->unblock();
            curContainer = nullptr;
            result = "You entered room ";
            result += std::to_string(roomNumber);
            result += ".";
        }
        break;
    case Lbr::ActOpen:
        if(!door->isLocked())
            result = "Door already opened.";
        else
            result = OpenLock(door->getLock());
        break;
    case Lbr::ActInspect:
        result = "You see door with number ";
        result += std::to_string(door->getNumber());
        if(door->getLock())
            result += " and " + door->getLock()->getNameString();
        result += ".";
        break;
    default:
        result = "Impossible action with the door.";
    }
    return result;
}

std::string Game::ActionWithInscription(Lbr::ActType aType,
                                        Inscription *inscription)
{
    std::string result;
    switch(aType) {
    case Lbr::ActRead:
    case Lbr::ActInspect:
        result = "\"" + inscription->getInscription() + "\"";
        break;
    default:
        result = "Impossible action with the inscription.";
    }
    return result;

}

std::string Game::ActionWithKey(Lbr::ActType aType, Key *key)
{
    std::string result;
    switch(aType) {
    case Lbr::ActInspect:
        result = "Key with number ";
        result += std::to_string(key->getNumber()) + ".";
        break;
    case Lbr::ActTake:
        break;
    case Lbr::ActThrow:
        break;
    default:
        result = "Impossible action with the key.";
    }
    return result;

}

std::string Game::OpenLock(LbrLock *lock)
{
    std::string result;
    Action act;
    if(lock->getName() == Lbr::ObjKeyLock) {
        act.oName = Lbr::ObjKey;
        Key *key = backpack->findKey(static_cast<Door*>(curContainer)->getNumber());
        if(!key)
            result = "Need a key.";
        else {
            if(static_cast<KeyLock*>(lock)->openLock(*key))
                result = "Opened.";
            else
                result = "The key does't fit.";
        }
    }
    else if(lock->getName() == Lbr::ObjKeyLock) {
    }
    return result;
}

std::string Game::ActionWithRoom(Lbr::ActType aType, Room *room)
{
    std::string result;
    switch(aType) {
    case Lbr::ActInspect:
        result = "Room number ";
        result += std::to_string(room->getNumber());
        result += '.';
        break;
    default:
        result = "Impossible. You can just inspect the room.";
    }
    return result;
}

std::string Game::ActionWithSheet(Lbr::ActType aType, Sheet *sheet)
{
    std::string result;
    switch(aType) {
    case Lbr::ActInspect:
        result = "Record: ";
        result += sheet->getRecord();
        break;
    case Lbr::ActTake:
        break;
    case Lbr::ActThrow:
        break;
    default:
        result = "Impossible action with the sheet.";
    }
    return result;
}

std::string Game::ActionWithShelf(Lbr::ActType aType)
{
    std::string result;
    Shelf *shelf = static_cast<Shelf*>(curContainer);
    switch(aType) {
    case Lbr::ActInspect:
        result = "In shelf: ";
        result += LbrObjectsList<LbrObject>(shelf->getObjects());
        break;
    default:
        result = "Impossible action with the shelf.";
    }
    return result;
}

std::string Game::ActionWithWall(Lbr::ActType aType)
{
    std::string result;
    Wall *wall;
    switch(aType) {
    case Lbr::ActInspect:
        result = "You see: ";
        wall = gameMap[roomNumber]->getWall(curWallType);
        result += LbrObjectsList<LbrContainer>(wall->getContainers());
        break;
    default:
        result = "Impossible. You can just inspect the wall.";
    }
    return result;
}

std::string Game::ActionWithWatch(Lbr::ActType aType, Watch *watch)
{
    std::string result;
    switch(aType) {
    case Lbr::ActInspect:
        result = "Time is " + watch->getTime();
    case Lbr::ActTake:
        break;
    case Lbr::ActThrow:
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
