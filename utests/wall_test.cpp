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
#include "door.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(WallGroup)
{
    Wall *wall = nullptr;
    Door *door = nullptr;
    int door_num = 6;
    void setup()
    {
        wall = new Wall();
        door = new Door(door_num);
    }
    void teardown()
    {
        delete wall;
        delete door;
    }
};

TEST(WallGroup, AddOContainer)
{
    CHECK(wall->addContainer(door));
    CHECK_FALSE(wall->addContainer(door)); //re-adding
}

TEST(WallGroup, GetName)
{
    CHECK_EQUAL(Lbr::ObjWall, wall->getName());
}

TEST(WallGroup, GetNameString)
{
    CHECK_EQUAL("wall", wall->getNameString());
}

TEST(WallGroup, FindContainer)
{
    CHECK(wall->addContainer(door));
    CHECK_EQUAL(door, wall->findContainer(Action(Lbr::ActNone, Lbr::ObjDoor)));
}

TEST(WallGroup, GetWallType)
{
    CHECK_EQUAL(Lbr::WallNone, Wall::getWallType(Lbr::ObjDoor));
    CHECK_EQUAL(Lbr::WallRight, Wall::getWallType(Lbr::ObjWallRight));
}

TEST(WallGroup, GetContainers)
{
    CHECK(wall->addContainer(door));
    CHECK_EQUAL(door, wall->getContainers()[0]);
}
