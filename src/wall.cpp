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
#include <algorithm>

Wall::~Wall()
{
    if(containers.size())
        for(auto c : containers) {
            delete c;
            c = nullptr;
        }
}

bool Wall::addContainer(LbrContainer *container)
{
    bool result = false;
    if(container && containers.size() < maxCapacity) {
        auto it = find(containers.begin(), containers.end(), container);
        if(it == containers.end()) {   //preventing re-adding
            containers.push_back(container);
            result = true;
        }
    }
    return result;
}

bool Wall::removeContainer(LbrContainer *container)
{
    bool result = false;
    auto it = find(containers.begin(), containers.end(), container);
    if(container && it != containers.end()) {
        containers.erase(it);
        result = true;
    }
    return result;
}

LbrContainer* Wall::findContainer(const Action act)
{
    if(containers.empty())
        return nullptr;
    LbrContainer *by_word = nullptr;
    if(act.oName != Lbr::ObjNone) {
        for(auto o : containers) {
            if(o->getName() == act.oName) {
                by_word = o;
                break;
            }
        }
    }
    LbrContainer *by_number = nullptr;
    decltype(containers.size()) num = act.number;
    if(act.number != -1 && num < containers.size())
        by_number = containers[num];
    if(!by_number)
        return by_word;
    else if(!by_word)
        return by_number;
    else if(by_word->getName() == by_number->getName())
        return by_number;
    return by_word;
}

Lbr::WallType Wall::getWallType(const Lbr::ObjName name)
{
    switch(name) {
    case Lbr::ObjWallTop:
        return Lbr::WallTop;
    case Lbr::ObjWallDown:
        return Lbr::WallDown;
    case Lbr::ObjWallLeft:
        return Lbr::WallLeft;
    case Lbr::ObjWallRight:
        return Lbr::WallRight;
    default:                         //invalid type argument
        return Lbr::WallNone;
    }
    return Lbr::WallNone;
}
