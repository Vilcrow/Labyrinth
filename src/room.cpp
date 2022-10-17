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
    walls[Lbr::WallTop] = nullptr;
    delete walls[Lbr::WallDown];
    walls[Lbr::WallDown] = nullptr;
    delete walls[Lbr::WallLeft];
    walls[Lbr::WallLeft] = nullptr;
    delete walls[Lbr::WallRight];
    walls[Lbr::WallRight] = nullptr;
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
