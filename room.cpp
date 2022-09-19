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

#include <vector>
#include "room.h"

RoomObject::RoomObject(int num) : LabyrinthObject(Labyrinth::ObjectRoom)
                                , number(num)
{
    top = new WallContainer();
    down = new WallContainer();
    left = new WallContainer();
    right = new WallContainer();
    currentWall = top;
    wallType = Labyrinth::WallTop;
}
//add object to corresponding wall
void RoomObject::addObject(Labyrinth::WallType wall, LabyrinthObject *obj)
{
    switch(wall) {
    case Labyrinth::WallNone:
        break;
    case Labyrinth::WallTop:
        top->addObject(obj);
        break;
    case Labyrinth::WallDown:
        down->addObject(obj);
        break;
    case Labyrinth::WallLeft:
        left->addObject(obj);
        break;
    case Labyrinth::WallRight:
        right->addObject(obj);
        break;
    }
}

void RoomObject::setCurrentWall(Labyrinth::WallType type)
{
    switch(type) {
    case Labyrinth::WallNone:
        break;
    case Labyrinth::WallTop:
        currentWall = top;
        break;
    case Labyrinth::WallDown:
        currentWall = down;
        break;
    case Labyrinth::WallLeft:
        currentWall = left;
        break;
    case Labyrinth::WallRight:
        currentWall = right;
        break;
    }
    wallType = type;
}

RoomObject::~RoomObject()
{
    delete top;
    delete down;
    delete left;
    delete right;
}

DoorObject* RoomObject::findDoor(int num) const
{
    DoorObject *result = nullptr;
    std::vector<WallContainer*> walls = {top, down, left, right};
    Action act(Labyrinth::ActionNone, Labyrinth::ObjectDoor);
    for(auto ptr : walls) {
        result = static_cast<DoorObject*>(ptr->findObject(act));
        if(result && result->getNumber() == num)
            return result;
    }
    return result;
}
