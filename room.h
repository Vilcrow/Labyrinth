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

#include <memory>
#include "labyrinth.h"
#include "wall.h"
#include "door.h"

class RoomObject : public LabyrinthObject {
    int number;
    WallContainer *top;
    WallContainer *down;
    WallContainer *left;
    WallContainer *right;
    WallContainer *currentWall;
    Labyrinth::WallType wallType;
public:
    RoomObject(int num);
    virtual ~RoomObject();
    void addObject(Labyrinth::WallType wall, LabyrinthObject *obj);
    void setCurrentWall(Labyrinth::WallType type);
    int getNumber() const { return number; }
    WallContainer* getCurrentWall() { return currentWall; }
    Labyrinth::WallType getCurrentWallType() { return wallType; }
    std::string handleAction(const Action& act) override;
    std::string getName() const override { return "room"; }
    DoorObject* findDoor(int num) const;
};

#endif
