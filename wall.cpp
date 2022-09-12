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

#include "commands.h"
#include "wall.h"

WallObject::WallObject() : LabyrinthObject(Labyrinth::ObjectWall)
{

}

void WallObject::addObject(LabyrinthObject *obj)
{
    objects.push_back(obj);
}

std::string WallObject::handleAction(const Action& act)
{
    std::string result;
    switch(act.aType) {
    case Labyrinth::ActionInspect:
        result = "You see: ";
        result += Commands::objectsList(objects);
        break;
    case Labyrinth::ActionOpen:
    case Labyrinth::ActionClose:
    case Labyrinth::ActionTake:
    case Labyrinth::ActionUse:
    default:
        result = "Impossible. You can just inspect the wall.";
    }
    return result;
}

LabyrinthObject* WallObject::findObject(Labyrinth::ObjectType type)
{
    if(objects.empty())
        return nullptr;
    for(auto o : objects) {
        if(o->getType() == type) 
            return o;
    }
    return nullptr;
}

Labyrinth::WallType WallObject::getWallType(const Labyrinth::ObjectType type)
{
    switch(type) {
    case Labyrinth::ObjectWallTop:
        return Labyrinth::WallTop;
    case Labyrinth::ObjectWallDown:
        return Labyrinth::WallDown;
    case Labyrinth::ObjectWallLeft:
        return Labyrinth::WallLeft;
    case Labyrinth::ObjectWallRight:
        return Labyrinth::WallRight;
    default:                         //invalid type argument
        return Labyrinth::WallNone;
    }
    return Labyrinth::WallNone;
}
