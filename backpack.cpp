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

#include "backpack.h"
#include "commands.h"

BackpackObject::BackpackObject() : LabyrinthObject(Labyrinth::ObjectBackpack)
                                 , capacity(maxCapacity)
{

}

bool BackpackObject::addObject(LabyrinthObject *obj)
{
    if(capacity > 0) {
        inventory.push_back(obj);
        --capacity;
        return true;
    }
    return false; //backpack is full;
}

bool BackpackObject::removeObject(LabyrinthObject *obj)
{
    //check the presence of an object in the backpack
    //and remove it
    return false;
}

std::string BackpackObject::handleAction(const Action& act)
{
    std::string result;
    switch(act.aType) {
    case Labyrinth::ActionInspect:
        result = Commands::objectsList(inventory);
        break;
    default:
        result = "Impossible.";
    }
    return result;
}
