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
#include <fstream>

Game::Game()
{
    setStartOptions();
}

Game::~Game()
{
    clearGameOptions();
}

void Game::setStartOptions()
{
    roomNumber = 1;
    curWallType = Lbr::WallTop;
    backpack = new Backpack();
    generateMap();
    curContainer = nullptr;
    saved = true;
}

void Game::clearGameOptions()
{
    delete backpack;
    backpack = nullptr;
    for(int i = 1; i <= roomCount; i++) {
        delete gameMap[i];
    }
    gameMap.clear();
}

void Game::run()
{
    std::string input, result;
    bool quit_game = false;
    std::cout << getContext() + "> ";
    while(!quit_game && std::getline(std::cin, input)) {
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
                std::cout << result << std::endl;
                std::cout << getContext() + "> ";
                continue;
            }
            else if(action.aType == Lbr::ActLoad) {
                result = load();
                std::cout << result << std::endl;
                std::cout << getContext() + "> ";
                continue;
            }
            else if(action.aType == Lbr::ActQuit) {
                result = quit(quit_game);
                std::cout << result << std::endl;
                if(!quit_game)
                    std::cout << getContext() + "> ";
                continue;
            }
            else
                result = "Specify the object.";
        }
        else
            result = ActionInGame(action);
        saved = false;
        COMMANDS->addCommand(input);
        std::cout << result << std::endl;
        std::cout << getContext() + "> ";
    }
}

std::string Game::ActionInGame(Action action)
{
    std::string result;
/*
    if(action.aType == Lbr::ActSave || action.aType == Lbr::ActLoad
                                    || action.aType == Lbr::ActQuit)
*/
    if(action.oName == Lbr::ObjNone && action.number == -1)
        result = "Invalid input.";
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
    return result;
}

void Game::generateMap()
{
    for(int i = 1; i <= roomCount; i++) {
        gameMap[i] = new Room(i);
    }
    //pointers
    Cassette *cassette = nullptr;
    Key *key = nullptr;
    Player *player = nullptr;
    Safe *safe = nullptr;
    Shelf *shelf = nullptr;
    Sheet *sheet = nullptr;
    Table *table = nullptr;
    Watch *watch = nullptr;

    //ROOM 1
    //wall TOP
    gameMap[1]->addDoorWithLock(Lbr::WallTop, Lbr::LockKey, 2);
    shelf = new Shelf();
    key = new Key(4);
    shelf->addObject(key);
    sheet = new Sheet("d8 - 1833");
    shelf->addObject(sheet);
    gameMap[1]->addContainer(Lbr::WallTop, shelf);
    //wall LEFT
    gameMap[1]->addDoorWithLock(Lbr::WallLeft, Lbr::LockKey, 4);
    safe = new Safe(735216);
    watch = new Watch("12:45");
    safe->addObject(watch);
    gameMap[1]->addContainer(Lbr::WallLeft, safe);
    //wall DOWN
    gameMap[1]->addDoorWithLock(Lbr::WallDown, Lbr::LockDigital, 6, 1245);
    shelf = new Shelf();
    sheet = new Sheet("Qui quaerit, reperit.");
    shelf->addObject(sheet);
    gameMap[1]->addContainer(Lbr::WallDown, shelf);
    //wall RIGHT
    gameMap[1]->addDoorWithLock(Lbr::WallRight, Lbr::LockDigital, 6, 1833);

    //ROOM 2
    //wall TOP
    //always closed door
    gameMap[2]->addDoorWithLock(Lbr::WallTop, Lbr::LockKey, 11);
    //wall LEFT
    //always closed door
    gameMap[2]->addDoorWithLock(Lbr::WallLeft, Lbr::LockKey, 3);
    //wall DOWN
    gameMap[2]->addDoorWithLock(Lbr::WallDown, Lbr::LockKey, 1);
    //wall RIGHT

    //ROOM 3
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //always closed door
    gameMap[3]->addDoorWithLock(Lbr::WallRight, Lbr::LockKey, 2);

    //ROOM 4
    //wall TOP
    //wall LEFT
    //wall DOWN
    //always closed door
    gameMap[4]->addDoorWithLock(Lbr::WallDown, Lbr::LockKey, 5);
    //wall RIGHT
    gameMap[4]->addDoorWithLock(Lbr::WallRight, Lbr::LockKey, 1);

    //ROOM 5
    //wall TOP
    //always closed door
    gameMap[5]->addDoorWithLock(Lbr::WallTop, Lbr::LockKey, 4);
    //wall LEFT
    //wall DOWN
    //wall RIGHT

    //ROOM 6
    //wall TOP
    gameMap[6]->addDoorWithLock(Lbr::WallTop, Lbr::LockDigital, 1, 1245);
    //wall LEFT
    //wall DOWN
    //wall RIGHT

    //ROOM 7
    //wall TOP
    //always closed door
    gameMap[7]->addDoorWithLock(Lbr::WallTop, Lbr::LockKey, 8);
    //wall LEFT
    //wall DOWN
    //wall RIGHT

    //ROOM 8
    //wall TOP
    //always closed door
    gameMap[8]->addDoorWithLock(Lbr::WallTop, Lbr::LockKey, 9);
    table = new Table();
    key = new Key(2);
    table->addObject(key);
    gameMap[8]->addContainer(Lbr::WallTop, table);
    //wall LEFT
    gameMap[8]->addDoorWithLock(Lbr::WallLeft, Lbr::LockDigital, 1, 1833);
    //wall DOWN
    //always closed door
    gameMap[8]->addDoorWithLock(Lbr::WallDown, Lbr::LockKey, 7);
    //wall RIGHT
    gameMap[8]->addDoorWithLock(Lbr::WallRight, Lbr::LockKey, 23);

    //ROOM 9
    //wall TOP
    //wall LEFT
    //wall DOWN
    //always closed door
    gameMap[9]->addDoorWithLock(Lbr::WallDown, Lbr::LockKey, 8);
    //wall RIGHT

    //ROOM 11
    //wall TOP
    //wall LEFT
    //wall DOWN
    //always closed door
    gameMap[11]->addDoorWithLock(Lbr::WallDown, Lbr::LockKey, 2);
    //wall RIGHT

    //ROOM 22
    //wall TOP
    //always closed door
    gameMap[22]->addDoorWithLock(Lbr::WallTop, Lbr::LockKey, 22);
    //wall LEFT
    //wall DOWN
    //wall RIGHT

    //ROOM 23
    //wall TOP
    //wall LEFT
    gameMap[23]->addDoorWithLock(Lbr::WallTop, Lbr::LockKey, 8);
    //wall DOWN
    //always closed door
    gameMap[23]->addDoorWithLock(Lbr::WallDown, Lbr::LockKey, 22);
    //wall RIGHT

    //ROOM 49
    //wall TOP
    //always closed door
    gameMap[49]->addDoorWithLock(Lbr::WallTop, Lbr::LockKey, 50);
    //wall LEFT
    //wall DOWN
    //wall RIGHT

    //ROOM 50
    //wall LEFT
    //always closed door
    gameMap[50]->addDoorWithLock(Lbr::WallLeft, Lbr::LockKey, 51);
    safe = new Safe(8934234);
    key = new Key(66);
    safe->addObject(key);
    //wall DOWN
    //always closed door
    gameMap[50]->addDoorWithLock(Lbr::WallDown, Lbr::LockKey, 49);
    //wall RIGHT

    //ROOM 51
    //wall LEFT
    //wall DOWN
    //wall RIGHT
    //always closed door
    gameMap[51]->addDoorWithLock(Lbr::WallRight, Lbr::LockKey, 51);

    //ROOM 52
    //wall LEFT
    //wall DOWN
    //wall RIGHT

    //ROOM 53
    //wall LEFT
    //wall DOWN
    //wall RIGHT

    //ROOM 54
    //wall LEFT
    //wall DOWN
    //wall RIGHT

    //ROOM 55
    //wall LEFT
    //wall DOWN
    //wall RIGHT

    //ROOM 56
    //wall LEFT
    //wall DOWN
    //wall RIGHT

    //ROOM 57
    //wall DOWN
    //wall RIGHT

    //ROOM 58
    //wall TOP
    //wall DOWN
    //wall RIGHT

    //ROOM 59
    //wall TOP
    //wall DOWN
    //wall RIGHT

    //ROOM 60
    //wall TOP
    //wall DOWN
    //wall RIGHT

    //ROOM 61
    //wall TOP
    //wall DOWN
    //wall RIGHT

    //ROOM 62
    //wall TOP
    //wall DOWN
    //wall RIGHT

    //ROOM 63
    //wall TOP
    //wall DOWN
    //wall RIGHT

    //ROOM 64
    //wall TOP
    //wall DOWN
    //wall RIGHT

    //ROOM 65
    //wall TOP
    //wall RIGHT

    //ROOM 66
    //wall TOP
    //wall LEFT
    //wall DOWN
    gameMap[66] = addDoorWithLock(Lbr::WallDown, Lbr::LockKey, finishRoom);
    //wall RIGHT

    //ROOM 67
    //wall TOP
    //wall LEFT
    //wall RIGHT

    //ROOM 68
    //wall TOP
    //wall LEFT
    //wall RIGHT

    //ROOM 69
    //wall TOP
    //wall LEFT
    //wall RIGHT

    //ROOM 70
    //wall TOP
    //wall LEFT
    //wall RIGHT

    //ROOM 71
    //wall TOP
    //wall LEFT
    //wall RIGHT

    //ROOM 72
    //wall TOP
    //wall LEFT
    //wall DOWN
    //wall RIGHT

    //ROOM 73
    //wall TOP
    //wall LEFT

    //ROOM 74
    //wall TOP
    //wall LEFT
    //wall DOWN

    //ROOM 75
    //wall TOP
    //wall LEFT
    //wall DOWN

    //ROOM 76
    //wall TOP
    //wall LEFT
    //wall DOWN

    //ROOM 77
    //wall TOP
    //wall LEFT
    //wall DOWN

    //ROOM 78
    //wall TOP
    //wall LEFT
    //wall DOWN

    //ROOM 79
    //wall TOP
    //wall LEFT
    //wall DOWN

    //ROOM 80
    //wall TOP
    //wall LEFT
    //wall DOWN

    //ROOM 81
    //wall LEFT
    gameMap[81]->addDoorWithLock(Lbr::WallLeft, Lbr::LockDigital, 50, 8923);
    //wall DOWN
    gameMap[81]->addDoorWithLock(Lbr::WallDown, Lbr::LockKey, 80);
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
    case Lbr::ObjTable:
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
        result = ActionWithDoor(act);
        break;
    case Lbr::ObjFlashlight:
        break;
    case Lbr::ObjPlayer:
        result = ActionWithPlayer(act.aType);
        break;
    case Lbr::ObjSafe:
        result = ActionWithSafe(act);
        break;
    case Lbr::ObjShelf:
        result = ActionWithShelf(act.aType);
        break;
    case Lbr::ObjTable:
        result = ActionWithTable(act.aType);
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

std::string Game::ActionWithDoor(const Action act)
{
    Door *door = static_cast<Door*>(curContainer);
    std::string result;
    switch(act.aType) {
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
            result = OpenLock(act, door->getLock());
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

std::string Game::OpenLock(const Action act, LbrLock *lock)
{
    std::string result;
    switch(lock->getType()) {
    case Lbr::LockNone:
        break;
    case Lbr::LockDigital:
        if(act.code == -1)
            result = "Usage: <action> <object> <number> <code>.";
        else if(static_cast<DigitalLock*>(lock)->openLock(act.code))
            result = "Opened.";
        else
            result = "Incorrect code.";
        break;
    case Lbr::LockKey:
    {
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

std::string Game::ActionWithSafe(const Action act)
{
    std::string result;
    Safe *safe = static_cast<Safe*>(curContainer);
    if(safe->isLocked()) //restricting access to a safe if it locked
        curContainer = nullptr;
    switch(act.aType) {
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
        else if(act.code == -1)
            result = "Usage: <acton> <object> <number> <code>.";
        else if(safe->openSafe(act.code))
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

std::string Game::ActionWithTable(Lbr::ActType aType)
{
    std::string result;
    Table *table = static_cast<Table*>(curContainer);
    switch(aType) {
    case Lbr::ActInspect:
        result = "On table: ";
        result += LbrObjectsList<LbrObject>(table->getObjects());
        break;
    default:
        result = "Impossible action with the table.";
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
    std::string result;
    if(COMMANDS->getHistory().empty())
        result = "No data to save.";
    else {
        std::ofstream file;
        std::string name;
        std::cout << "File name to write: ";
        std::cin >> name;
        file.open(name);
        if(file.is_open()) {
            for(auto c : COMMANDS->getHistory())
                file << c << std::endl;
            file.close();
            saved = true;
            result = "Saved.";
        }
        else
            result = "Couldn't open the file.";
    }
    return result;
}

std::string Game::load()
{
    std::string result;
    std::string input;
    bool discard = true;
    if(!COMMANDS->getHistory().empty()) {
        std::cout << "The progress of the current game will be lost. "
                     "Continue?[y/n]: ";
        std::cin >> input;
        for(auto& c : input)
            c = std::tolower(c);
        if(input.find('y') != std::string::npos)
            discard = true;
        else
            discard = false;
    }
    if(discard) {
        std::cout << "File name to load: ";
        std::string name;
        std::cin >> name;
        std::ifstream file;
        file.open(name);
        if(file.is_open()) {
            COMMANDS->clearHistory();
            clearGameOptions();
            setStartOptions();
            std::string command;
            while(std::getline(file, command)) {
                Action act = COMMANDS->cmdToAction(command);
                ActionInGame(act);
                COMMANDS->addCommand(command);
            }
            file.close();
            saved = true;
            result = "Loaded.";
        }
        else
            result = "Couldn't open the file.";
    }
    else
        result = "Cancelled.";
    return result;
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

std::string Game::quit(bool& q)
{
    std::string result;
    std::string input;
    if(!saved) {
        if(!COMMANDS->getHistory().empty()) {
            std::cout << "The progress of the current game will be lost. "
                         "Save?[y/n/c]: ";
            std::cin >> input;
            for(auto& c : input)
                c = std::tolower(c);
            if(input.find('y') != std::string::npos) {
                result = save();
                if(saved) {
                    q = true;
                    result += " Bye.";
                }
            }
            else if(input.find('c') != std::string::npos) {
                result = "Canceled.";
                q = false;
            }
            else {
                result = "Bye.";
                q = true;
            }
        }
    }
    else {
        result = "Bye.";
        q = true;
    }
    return result;
}
//TBD
std::string Game::checkDoors() const
{
    std::string result = "OK";
    return result;
}
