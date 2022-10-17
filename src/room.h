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

#ifndef ROOM_H_SENTRY
#define ROOM_H_SENTRY

#include "labyrinth.h"
#include "door.h"
#include "wall.h"
#include <map>

class Room {
public:
    Room(int num);
    virtual ~Room();
    bool addContainer(Lbr::WallType wType, LbrContainer *container);
    bool removeContainer(Lbr::WallType wType, LbrContainer *container);
    int getNumber() const { return number; }
    Lbr::ObjName getName() { return Lbr::ObjRoom; }
    std::string getNameString() const { return "room"; }
    Door* findDoor(int num) const;
    Wall* getWall(Lbr::WallType wType) { return walls[wType]; }
private:
    int number;
    std::map<Lbr::WallType, Wall*> walls;
};

#endif
