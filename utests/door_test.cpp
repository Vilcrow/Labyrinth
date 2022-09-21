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
#include "door.h"

TEST_GROUP(DoorGroup)
{
    DoorObject *door;
    int number = 10;

    void setup()
    {
        door = new DoorObject(number);
    }
    void teardown()
    {
        delete door;
    }
};

TEST(DoorGroup, GetNumber)
{
    CHECK_EQUAL(number, door->getNumber());
}

TEST(DoorGroup, SetNumber)
{
    door->setNumber(5);
    CHECK_EQUAL(5, door->getNumber());
}

TEST(DoorGroup, IsLockedAndSetLocked)
{
    CHECK(door->isLocked());
    door->setLocked(false);
    CHECK_FALSE(door->isLocked());
    door->setLocked(true);
    CHECK(door->isLocked());
}

TEST(DoorGroup, GetName)
{
    CHECK_EQUAL("door", door->getName());
}
