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

#include "room.h"
#include "keylock.h"
#include "digitallock.h"

Room::Room(int num) : number(num)
{
    walls[Lbr::WallTop] = new Wall();
    walls[Lbr::WallDown] = new Wall();
    walls[Lbr::WallLeft] = new Wall();
    walls[Lbr::WallRight] = new Wall();
}
Room::~Room()
{
    delete walls[Lbr::WallTop];
    delete walls[Lbr::WallDown];
    delete walls[Lbr::WallLeft];
    delete walls[Lbr::WallRight];
    walls.clear();
}

//add container object to corresponding wall
bool Room::addContainer(Lbr::WallType wType, LbrContainer *container)
{
    bool result = false;
    if(wType != Lbr::WallNone)
        result = walls[wType]->addContainer(container);
    return result;
}

//remove container object from corresponding wall
bool Room::removeContainer(Lbr::WallType wType, LbrContainer *container)
{
    bool result = false;
    if(wType != Lbr::WallNone)
        result = walls[wType]->removeContainer(container);
    return result;
}

Door* Room::findDoor(int num) const
{
    Door *result = nullptr;
    Action act(Lbr::ActNone, Lbr::ObjDoor);
    for(const auto& w : walls) {
        result = static_cast<Door*>(w.second->findContainer(act));
        if(result && result->getNumber() == num)
            return result;
    }
    return result;
}
//find door in corresponding wall
//second argument is the last found door
Door* Room::findDoor(Lbr::WallType wType, const Door *door) //maybe need fix
{
    Door *result = nullptr;
    Action act;
    int c_size = walls[wType]->getContainers().size();
    for(int i = 0; i < c_size; i++) {
        act.number = i;
        LbrContainer *container = walls[wType]->findContainer(act);
        if(container->getName() == Lbr::ObjDoor &&
           static_cast<Door*>(container) != door) {
            result = static_cast<Door*>(container);
            break;
        }
    }
    return result;
}

bool Room::addDoorWithLock(Lbr::WallType wType, Lbr::LockType lockType
                                              , int number, int code)
{
    bool result = true;
    Door *door = new Door(number);
    LbrLock *lock = nullptr;
    switch(lockType) {
    case Lbr::LockNone:
        result = false;
        break;
    case Lbr::LockDigital:
        if(code == -1)
            result = false;
        lock = static_cast<LbrLock*>(new DigitalLock(code));
        break;
    case Lbr::LockKey:
        lock = static_cast<LbrLock*>(new KeyLock(number));
        break;
    }
    if(result) {
        result = door->addObject(lock);
        if(result)
            result = addContainer(wType, door);
    }
    return result;
}
