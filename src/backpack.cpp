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
    if(!obj) //null pointer
        return false;
    if(capacity > 0) {
        inventory.push_back(obj);
        --capacity;
        return true;
    }
    return false; //backpack is full;
}

bool BackpackContainer::removeObject(LabyrinthObject *obj)
{
    if(!obj) //null pointer
        return false;
    auto it = find(inventory.begin(), inventory.end(), obj);
    if(it != inventory.end()) {
        inventory.erase(it);
        capacity++;
        return true;
    }
    return false;
}

LabyrinthObject* BackpackContainer::findObject(const Action act)
{
    if(inventory.empty())
        return nullptr;
    LabyrinthObject *by_word = nullptr;
    if(act.oType != Labyrinth::ObjectNone) {
        for(auto o : inventory) {
            if(o->getType() == act.oType) {
                by_word = o;
                break;
            }
        }
    }
    LabyrinthObject *by_number = nullptr;
    decltype(inventory.size()) num = act.number;
    if(act.number != -1 && num < inventory.size())
        by_number = inventory[num];
    if(!by_number)
        return by_word;
    else if(!by_word)
        return by_number;
    else if(by_word->getType() == by_number->getType())
        return by_number;
    return by_word;
}

KeyObject* BackpackContainer::findKey(int num)
{
    KeyObject *result = nullptr;
    if(inventory.empty())
        return result;
    for(auto o : inventory) {
        if(o->getType() == Labyrinth::ObjectKey) {
            if(static_cast<KeyObject*>(o)->getNumber() == num) {
                result = static_cast<KeyObject*>(o);
                break;
            }
        }
    }
    return result;
}
