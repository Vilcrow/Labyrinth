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

#ifndef LABYRINTH_H_SENTRY
#define LABYRINTH_H_SENTRY

#include <string>

struct Action;

//Class namespace for various enums
class Labyrinth {
public:
    enum ActionType {
                     ActionNone,
                     ActionClose,
                     ActionEnter,
                     ActionInspect,
                     ActionOpen,
                     ActionPush,
                     ActionPull,
                     ActionTake,
                     ActionThrow,
                     ActionUse
    };
    enum ObjectType {
                     ObjectNone,
                     ObjectBackpack,
                     ObjectBattery,
                     ObjectDoor,
                     ObjectFlashlight,
                     ObjectKey,
                     ObjectRoom,
                     ObjectSheet,
                     ObjectWall,
                     ObjectWallTop,
                     ObjectWallDown,
                     ObjectWallLeft,
                     ObjectWallRight,
                     ObjectWatch
    };
    enum WallType   {
                     WallNone,
                     WallDown,
                     WallLeft,
                     WallRight,
                     WallTop
    };

    Labyrinth() = delete;
    ~Labyrinth() = delete;
};
//parent of all other object classes
class LabyrinthObject {
    Labyrinth::ObjectType type;
public:
    LabyrinthObject(Labyrinth::ObjectType t) : type(t) {}
    virtual ~LabyrinthObject() {}
    Labyrinth::ObjectType getType() const { return type; }
    virtual std::string getName() const = 0;
};
//parent abstract class for container objects
//like BackpackContainer and WallContainer
class LabyrinthContainer {
public:
    LabyrinthContainer() = default;
    virtual ~LabyrinthContainer() = default;
    virtual bool addObject(LabyrinthObject *obj) = 0;
    virtual bool removeObject(LabyrinthObject *obj) = 0;
    virtual LabyrinthObject* findObject(const Action act) = 0;
    virtual std::string getName() const = 0; 
};

struct Action {
    Action(Labyrinth::ActionType act = Labyrinth::ActionNone,
           Labyrinth::ObjectType obj = Labyrinth::ObjectNone, int num = -1)
           : aType(act), oType(obj), number(num) {}
    Labyrinth::ActionType aType;
    Labyrinth::ObjectType oType;
    //number of object in container if we have more one
    //number == -1 - no specified
    int number;
};

#endif
