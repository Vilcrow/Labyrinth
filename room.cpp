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

RoomObject::RoomObject() : LabyrinthObject(Labyrinth::ObjectRoom)
{
    top = new WallObject();
    down = new WallObject();
    left = new WallObject();
    right = new WallObject();
    currentWall = top;
    wallType = Labyrinth::WallTop;
}
//add object to corresponding wall
void RoomObject::addObject(Labyrinth::WallType wall, LabyrinthObject *obj)
{
    switch(wall) {
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
    case Labyrinth::WallTop:
        currentWall = top;
    case Labyrinth::WallDown:
        currentWall = down;
    case Labyrinth::WallLeft:
        currentWall = left;
    case Labyrinth::WallRight:
        currentWall = right;
    }
    wallType = type;
}

std::string RoomObject::handleAction(const Action& act)
{
    return "OK";
}

RoomObject::~RoomObject()
{
    delete top;
    delete down;
    delete left;
    delete right;
}
