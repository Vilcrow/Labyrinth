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

#include <string>
#include "door.h"

DoorObject::DoorObject(int num, bool opnd)
                      : LabyrinthObject(Labyrinth::ObjectDoor)
                      , number(num), opened(opnd)
{

}

bool DoorObject::open(const KeyObject& key)
{
    if(number == key.getNumber()) {
        opened = true;
        return true;
    }
    else //key don't worked
        return false;
}

std::string DoorObject::handleAction(const Action& act) //need elaboration
{
    std::string result;
    switch(act.aType) {
    case Labyrinth::ActionClose:
        if(!opened)
            result = "Door already closed.";
        else {
            opened = false;  //good idea?
            result = "You close the door.";
        }
        break;
    case Labyrinth::ActionOpen:
        if(opened)
            result = "Door already opened.";
        else {
            opened = true;
            result = "You open the door.";
        }
        break;
    case Labyrinth::ActionInspect:
        result = "You see door with number ";
        result += std::to_string(number) + ".";
        break;
    default:
        result = "Impossible.";
    }
    return result;
}

std::string KeyObject::handleAction(const Action& act)
{
    std::string result;
    switch(act.aType) {
    case Labyrinth::ActionInspect:
        result = "You see key with number ";
        result += std::to_string(number) + ".";
        break;
    default:
        result = "Impossible.";
    }
    return result;
}
