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

#include "labyrinth.h"
#include <algorithm>

bool LbrContainer::addObject(LbrObject *obj)  //need make const?
{
    bool result = false;
    if(obj && objects.size() < maxCap) {
        auto it = find(objects.begin(), objects.end(), obj);
        if(it == objects.end()) {   //preventing re-adding
            objects.push_back(obj);
            result = true;
        }
    }
    return result;
}

bool LbrContainer::removeObject(LbrObject *obj)  //need make const?
{
    bool result = false;
    auto it = find(objects.begin(), objects.end(), obj);
    if(obj && it != objects.end()) {
        objects.erase(it);
        result = true;
    }
    return result;
}

LbrObject* LbrContainer::findObject(const Action act)
{
    if(objects.empty())
        return nullptr;
    LbrObject *by_word = nullptr;
    if(act.oName != Lbr::ObjNone) {
        for(auto o : objects) {
            if(o->getName() == act.oName) {
                by_word = o;
                break;
            }
        }
    }
    LbrObject *by_number = nullptr;
    decltype(objects.size()) num = act.number;
    if(act.number != -1 && num < objects.size())
        by_number = objects[num];
    if(!by_number)
        return by_word;
    else if(!by_word)
        return by_number;
    else if(by_word->getName() == by_number->getName())
        return by_number;
    return by_word;
}
