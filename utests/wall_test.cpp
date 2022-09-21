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

#include "wall.h"
#include "key.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(WallGroup)
{
    WallContainer *wall;
    KeyObject *key;
    Action act;

    void setup()
    {
        wall = new WallContainer();
        key = new KeyObject(5);
    }
    void teardown()
    {
        delete wall;
        delete key;
    }
};

TEST(WallGroup, AddObject)
{
    CHECK(wall->getObjects().empty());
    wall->addObject(key);
    act.oType = Labyrinth::ObjectKey;
    CHECK_EQUAL(key, wall->findObject(act));
    CHECK_FALSE(wall->getObjects().empty());
}

TEST(WallGroup, RemoveObject)
{
    CHECK(wall->getObjects().empty());
    wall->addObject(key);
    CHECK_FALSE(wall->getObjects().empty());
    wall->removeObject(key);
    CHECK(wall->getObjects().empty());
}

TEST(WallGroup, GetName)
{
    CHECK_EQUAL("wall", wall->getName());
}

TEST(WallGroup, FindObject)
{
    CHECK(wall->getObjects().empty());
    wall->addObject(key);
    act.oType = Labyrinth::ObjectKey;
    CHECK_EQUAL(key, wall->findObject(act));
    CHECK_FALSE(wall->getObjects().empty());
}

TEST(WallGroup, GetWallType)
{
    CHECK_EQUAL(Labyrinth::WallTop,
                wall->getWallType(Labyrinth::ObjectWallTop));
    CHECK_EQUAL(Labyrinth::WallDown,
                wall->getWallType(Labyrinth::ObjectWallDown));
    CHECK_EQUAL(Labyrinth::WallLeft,
                wall->getWallType(Labyrinth::ObjectWallLeft));
    CHECK_EQUAL(Labyrinth::WallRight,
                wall->getWallType(Labyrinth::ObjectWallRight));
    //for non-wall object
    CHECK_EQUAL(Labyrinth::WallNone,
                wall->getWallType(Labyrinth::ObjectDoor));
}

TEST(WallGroup, GetObjects)
{
    CHECK(wall->getObjects().empty());
    wall->addObject(key);
    CHECK_EQUAL(key, wall->getObjects()[0]);
}
