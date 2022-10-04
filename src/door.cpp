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

#include "door.h"

Door::Door(int num) : LbrContainer(Lbr::ObjDoor), number(num)
{

}

bool Door::addLock(LbrLock *lock)
{
    bool result = false;
    if(locks.size() < maxCapacity) {
        locks.push_back(lock);
        result = true;
    }
    return result;
}

bool Door::isLocked() const
{
    bool result = false;
    if(locks.empty())
        result = false;
    else {
        for(const auto& l : locks) {
            if(l->isLocked()) {   //at least one lock is closed
                result = true;
                break;
            }
        }
    }
    return result;
}

bool Door::addObject(LbrObject *obj) {return false;}
bool Door::removeObject(LbrObject *obj) {return false;}
LbrObject* Door::findObject(const Action act) {return nullptr;}
