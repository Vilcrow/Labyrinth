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

#include <algorithm>
#include "backpack.h"
#include "commands.h"

BackpackContainer::BackpackContainer() : LabyrinthContainer()
                                       , capacity(maxCapacity)
{

}

bool BackpackContainer::addObject(LabyrinthObject *obj)
{
    if(capacity > 0) {
        inventory.push_back(obj);
        --capacity;
        return true;
    }
    return false; //backpack is full;
}

bool BackpackContainer::removeObject(LabyrinthObject *obj)
{
    auto it = find(inventory.begin(), inventory.end(), obj);
    if(it != inventory.end()) {
        inventory.erase(it);
        return true;
    }
    return false;
}

std::string BackpackContainer::handleAction(const Action& act)
{
    std::string result;
    switch(act.aType) {
    case Labyrinth::ActionOpen:
    case Labyrinth::ActionInspect:
        result = "In backpack: ";
        result += Commands::objectsList(inventory);
        break;
    case Labyrinth::ActionClose:
        result = "Backpack closed.";
        break;
    default:
        result = "Impossible.";
    }
    return result;
}

LabyrinthObject* BackpackContainer::findObject(Labyrinth::ObjectType type)
{
    if(inventory.empty())
        return nullptr;
    for(auto o : inventory) {
        if(o->getType() == type) 
            return o;
    }
    return nullptr;
}
