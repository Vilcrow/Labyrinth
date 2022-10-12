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

#include "player.h"

Player::Player() : LbrContainer(Lbr::ObjPlayer, 1)
{

}

bool Player::addObject(LbrObject *obj)
{
    bool result = false;
    if(obj->getName() == Lbr::ObjCassette)
        result = LbrContainer::addObject(obj);
    return result;
}

std::string Player::getRecord() const
{
    std::string result = "Put the cassette.";
    LbrObject *obj = findObject(Action(Lbr::ActNone, Lbr::ObjCassette));
    if(obj) {
        Cassette *cassette = static_cast<Cassette*>(obj);
        result = cassette->getRecord();
    }
    return result;
}

Cassette* Player::getCassette() const
{
    LbrObject *obj = findObject(Action(Lbr::ActNone, Lbr::ObjCassette));
    Cassette *result = static_cast<Cassette*>(obj);
    return result;
}
