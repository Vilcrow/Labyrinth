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

Door::Door(int num) : LbrContainer(Lbr::ObjDoor, 1)
                    , number(num)
{

}

bool Door::addObject(LbrObject *obj)
{
    bool result = false;
    if(obj && obj->getName() == Lbr::ObjLock)
        result = LbrContainer::addObject(obj);
    return result;
}

bool Door::isLocked() const
{
    bool result = false;
    LbrLock *lock = nullptr;
    LbrObject *obj = findObject(Action(Lbr::ActNone, Lbr::ObjLock));
    if(obj && obj->getName() == Lbr::ObjLock)
        lock = static_cast<LbrLock*>(obj);
    if(lock && lock->isLocked())
        result = true;
    return result;
}

LbrLock* Door::getLock() const
{
    LbrLock *lock = nullptr;
    LbrObject *obj = findObject(Action(Lbr::ActNone, Lbr::ObjLock));
    if(obj && obj->getName() == Lbr::ObjLock)
        lock = static_cast<LbrLock*>(obj);
    return lock;
}

bool Door::setLocked(bool lckd)
{
    bool result = false;  //return false if lock don't exists
    LbrLock *lock = nullptr;
    LbrObject *obj = findObject(Action(Lbr::ActNone, Lbr::ObjLock));
    if(obj && obj->getName() == Lbr::ObjLock)
        lock = static_cast<LbrLock*>(obj);
    if(lock) {
        lock->setLocked(lckd); 
        result = true;
    }
    return result;
}
