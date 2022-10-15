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
#include "digitallock.h"
#include <iostream>

Game::Game()
{
    roomNumber = 1;
    curWallType = Lbr::WallTop;
    backpack = new Backpack();
    generateMap();
    curContainer = nullptr;
}

Game::~Game()
{
    delete backpack;
    backpack = nullptr;
    for(int i = 1; i <= roomCount; i++) {
        delete gameMap[i];
        gameMap[i] = nullptr;
    }
}

void Game::run()
{
    std::string input, result;
    std::cout << getContext() + "> ";
    while(std::getline(std::cin, input)) {
        if(input.empty()) {
            std::cout << getContext() + "> ";
            continue;
        }
        Action action = COMMANDS->cmdToAction(input);
        if(action.aType == Lbr::ActNone)
            result = "Specify the action.";
        else if(action.oName == Lbr::ObjNone && action.number == -1) {
            if(action.aType == Lbr::ActSave) {
                result = save();
            }
            else if(action.aType == Lbr::ActQuit)  //quit the game
//TBD
                break;
            else
                result = "Specify the object.";
        }
        else if(action.oName == Lbr::ObjBackpack) {
            curContainer = backpack;
            result = ActionWithBackpack(action.aType);
        }
        else if(action.oName == Lbr::ObjRoom) {
            curContainer = nullptr;
            result = ActionWithRoom(action.aType, gameMap[roomNumber]);
        }
        else if(action.oName == Lbr::ObjWall) {
            curContainer = nullptr;
            result = ActionWithWall(action.aType);
        }
        else if(action.oName == Lbr::ObjWallTop   ||
                action.oName == Lbr::ObjWallDown  ||
                action.oName == Lbr::ObjWallLeft  ||
                action.oName == Lbr::ObjWallRight) {
            curContainer = nullptr;
            curWallType = Wall::getWallType(action.oName);
            result = ActionWithWall(action.aType);
        }
        else {
            if(action.oName == Lbr::ObjNone && action.number != -1) {
                if(!curContainer) {
                    action.oType = Lbr::Container;
                }
                else {
                    action.oType = Lbr::Object;
                }
            }
            if(action.oType == Lbr::Object) {
                LbrObject *object = curContainer->findObject(action);
                if(!object && action.aType == Lbr::ActThrow)
                    object = backpack->findObject(action);
                if(!object)
                    result = "No such item.";
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
        std::cout << getContext() + "> ";
    }
}

void Game::generateMap()
{
    for(int i = 1; i <= roomCount; i++) {
        gameMap[i] = new Room(i);
    }
    Cassette *cassette = nullptr;
    DigitalLock *digitallock = nullptr;
    Door *door = nullptr;
    KeyLock *keylock = nullptr;
    Key *key = nullptr;
    Player *player = nullptr;
    Safe *safe = nullptr;
    Shelf *shelf = nullptr;
    Sheet *sheet = nullptr;
    Watch *watch = nullptr;
    //ROOM 1
    //wall TOP
    door = new Door(2);
    keylock = new KeyLock(2);
    door->addObject(keylock);
    gameMap[1]->addContainer(Lbr::WallTop, door);
    player = new Player();
    gameMap[1]->addContainer(Lbr::WallTop, player);
    //wall LEFT
    door = new Door(4);
    keylock = new KeyLock(4);
    door->addObject(keylock);
    gameMap[1]->addContainer(Lbr::WallLeft, door);
    shelf = new Shelf();
    key = new Key(2);
    shelf->addObject(key);
    watch = new Watch("11:53");
    shelf->addObject(watch);
    cassette = new Cassette("Cassette test.");
    shelf->addObject(cassette);
    gameMap[1]->addContainer(Lbr::WallLeft, shelf);
    //wall DOWN
    door = new Door(6);
    digitallock = new DigitalLock(1111);
    door->addObject(digitallock);
    gameMap[1]->addContainer(Lbr::WallDown, door);
    //wall RIGHT
    door = new Door(8);
    keylock = new KeyLock(8);
    door->addObject(keylock);
    gameMap[1]->addContainer(Lbr::WallRight, door);
    safe = new Safe(1153);
    sheet = new Sheet("Qui quaerit, reperit.");
    safe->addObject(sheet);
    gameMap[1]->addContainer(Lbr::WallRight, safe);
    //ROOM 2
    //wall TOP
    //wall LEFT
    //wall DOWN
    door = new Door(1);
    keylock = new KeyLock(1);
    door->addObject(keylock);
    gameMap[2]->addContainer(Lbr::WallDown, door);
    //wall RIGHT
    //ROOM 4
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    door = new Door(1);
    keylock = new KeyLock(1);
    door->addObject(keylock);
    gameMap[4]->addContainer(Lbr::WallRight, door);
    //ROOM 6
    //wall TOP
    door = new Door(1);
    digitallock = new DigitalLock(1111);
    door->addObject(digitallock);
    gameMap[6]->addContainer(Lbr::WallTop, door);
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //ROOM 8
    //wall TOP
    //wall LEFT
    door = new Door(1);
    keylock = new KeyLock(1);
    door->addObject(keylock);
    gameMap[8]->addContainer(Lbr::WallLeft, door);
    //wall DOWN
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
    case Lbr::ObjCassette:
        result = ActionWithCassette(act.aType, static_cast<Cassette*>(obj));
        break;
    case Lbr::ObjLock:
        result = ActionWithLock(act.aType, static_cast<LbrLock*>(obj));
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
    case Lbr::ObjDoor:
    case Lbr::ObjFlashlight:
    case Lbr::ObjLockDigital:
    case Lbr::ObjLockKey:
    case Lbr::ObjPlayer:
    case Lbr::ObjSafe:
    case Lbr::ObjShelf:
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
    case Lbr::ObjFlashlight:
        break;
    case Lbr::ObjPlayer:
        result = ActionWithPlayer(act.aType);
        break;
    case Lbr::ObjSafe:
        result = ActionWithSafe(act.aType);
        break;
    case Lbr::ObjShelf:
        result = ActionWithShelf(act.aType);
        break;
//no processing required
    case Lbr::ObjNone:
    case Lbr::ObjBackpack:
    case Lbr::ObjBattery:
    case Lbr::ObjCassette:
    case Lbr::ObjLockDigital:
    case Lbr::ObjInscription:
    case Lbr::ObjKey:
    case Lbr::ObjLock:
    case Lbr::ObjLockKey:
    case Lbr::ObjRoom:
    case Lbr::ObjSheet:
    case Lbr::ObjWatch:
    case Lbr::ObjWall:
    case Lbr::ObjWallDown:
    case Lbr::ObjWallLeft:
    case Lbr::ObjWallRight:
    case Lbr::ObjWallTop:
        break;
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
        result = ActionTakeObject(battery);
        break;
    case Lbr::ActThrow:
        result = ActionThrowObject(battery);
        break;
    default:
        result = "Impossible action with the battery.";
    }
    return result;
}

std::string Game::ActionWithCassette(Lbr::ActType aType, Cassette *cassette)
{
    std::string result;
    switch(aType) {
    case Lbr::ActInspect:
        result = "Audio cassette.";
        break;
    case Lbr::ActTake:
        result = ActionTakeObject(cassette);
        break;
    case Lbr::ActThrow:
        result = ActionThrowObject(cassette);
        break;
    default:
        result = "Impossible action with the cassette.";
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
            result = "The door is locked. You need to open it.";
        }
        else {
            int prev_room = roomNumber;
            Door *back_door;
            roomNumber = door->getNumber();
            //open the return door in current room
            back_door = gameMap[roomNumber]->findDoor(prev_room);
            if(back_door)
                back_door->setLocked(false);
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
            result += " and " + door->getLock()->getNameString() + "(0)";
        result += ".";
        break;
    default:
        result = "Impossible action with the door.";
    }
    //curContainer = nullptr;
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
        result = ActionTakeObject(key);
        break;
    case Lbr::ActThrow:
        result = ActionThrowObject(key);
        break;
    default:
        result = "Impossible action with the key.";
    }
    return result;
}

std::string Game::ActionWithLock(Lbr::ActType aType, LbrLock *lock)
{
    std::string result;
    switch(aType) {
    case Lbr::ActInspect:
        result = "You see a ";
        result += lock->getNameString() + ".";
        break;
    default:
        result = "Impossible action with the lock.";
    }
    return result;
}

std::string Game::ActionWithPlayer(Lbr::ActType aType)
{
    Player *player = static_cast<Player*>(curContainer);
    std::string result;
    switch(aType) {
    case Lbr::ActInspect:
        result = "In player: ";
        result += LbrObjectsList<LbrObject>(player->getObjects());
        break;
    case Lbr::ActPlay:
        result = player->getRecord();
        break;
    default:
        result = "Impossible action with the player.";
    }
    return result;

}

std::string Game::OpenLock(LbrLock *lock)
{
    std::string result;
    Action act;
    switch(lock->getType()) {
    case Lbr::LockNone:
        break;
    case Lbr::LockDigital:
        if(static_cast<DigitalLock*>(lock)->openLock())
            result = "Opened.";
        else
            result = "Incorrect code.";
        break;
    case Lbr::LockKey:
    {
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
        break;
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

std::string Game::ActionWithSafe(Lbr::ActType aType)
{
    std::string result;
    Safe *safe = static_cast<Safe*>(curContainer);
    if(safe->isLocked()) //restricting access to a safe if it locked
        curContainer = nullptr;
    switch(aType) {
    case Lbr::ActInspect:
        if(safe->isLocked())
            result = "You see locked safe.";
        else {
            result = "In safe: ";
            result += LbrObjectsList<LbrObject>(safe->getObjects());
        }
        break;
    case Lbr::ActOpen:
        if(!safe->isLocked())
            result = "The safe already opened.";
        else if(safe->openSafe())
            result = "The safe unlocked.";
        else
            result = "Incorrect code.";
        break;
    default:
        result = "Impossible action with the safe.";
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
        result = ActionTakeObject(sheet);
        break;
    case Lbr::ActThrow:
        result = ActionThrowObject(sheet);
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
        break;
    case Lbr::ActTake:
        result = ActionTakeObject(watch);
        break;
    case Lbr::ActThrow:
        result = ActionThrowObject(watch);
        break;
    default:
        result = "Impossible action with the watch.";
    }
    return result;
}

std::string Game::save()
{
    return "Saved.";
}

std::string Game::ActionTakeObject(LbrObject *obj)
{
    std::string result = "Impossible.";
    if(curContainer != backpack) {
        if(backpack->addObject(obj)) {
            curContainer->removeObject(obj);
            result = "Done.";
        }
    }
    else if(curContainer == backpack)
        result = "Already in backpack.";
    else if(backpack->getCapacity() == 0)
        result = "The backpack is full.";
    return result;
}

std::string Game::ActionThrowObject(LbrObject *obj)
{
    std::string result = "Impossible.";
    if(curContainer && curContainer != backpack) {
        if(curContainer->addObject(obj)) {
            backpack->removeObject(obj);
            result = "Done.";
        }
    }
    else if(!curContainer || curContainer == backpack)
        result = "Find a place to throw it away.";
    else if(curContainer && curContainer->getCapacity() == 0)
        result = "The " + curContainer->getNameString() + " is full.";
    return result;
}

std::string Game::getContext() const
{
    std::string result;
    std::string wall;
    switch(curWallType) {
    case Lbr::WallNone:
        break;
    case Lbr::WallDown:
        wall = "down";
        break;
    case Lbr::WallLeft:
        wall = "left";
        break;
    case Lbr::WallRight:
        wall = "right";
        break;
    case Lbr::WallTop:
        wall = "top";
        break;
    }
    std::string focus;
    if(curContainer)
        focus = curContainer->getNameString();
    else
        focus = "wall";
    result = "[R: " + std::to_string(roomNumber) + ", W: "  + wall
             + ", F: " + focus
             + "] ";
    return result;
}
