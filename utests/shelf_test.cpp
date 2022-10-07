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

#include "CppUTest/TestHarness.h"
#include "shelf.h"
#include "key.h"

TEST_GROUP(ShelfGroup)
{
    Shelf *shelf = nullptr;
    Key *key = nullptr;
    int key_num = 5;
    void setup()
    {
        shelf = new Shelf();
        key = new Key(key_num);
    }
    void teardown()
    {
        delete shelf;
        delete key;
    }
};

TEST(ShelfGroup, AddRemoveFindObject)
{
    CHECK(shelf->addObject(key));
    CHECK_FALSE(shelf->addObject(key));
    CHECK_EQUAL(key, shelf->findObject(Action(Lbr::ActNone, Lbr::ObjKey)));
    CHECK(shelf->removeObject(key));
    CHECK_FALSE(shelf->removeObject(key));
}

TEST(ShelfGroup, GetName)
{
    CHECK_EQUAL(Lbr::ObjShelf, shelf->getName());
}

TEST(ShelfGroup, GetNameString)
{
    CHECK_EQUAL("shelf", shelf->getNameString());
}
