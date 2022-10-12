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
#include "keylock.h"
#include "key.h"

TEST_GROUP(DoorGroup)
{
    Door *door = nullptr;
    KeyLock *keylock = nullptr;
    int door_num = 5;
    void setup()
    {
        door = new Door(door_num);
        keylock = new KeyLock(door_num);
    }
    void teardown()
    {
        delete door;
        delete keylock;
    }
};

TEST(DoorGroup, GetNumber)
{
    CHECK_EQUAL(door_num, door->getNumber());
}

TEST(DoorGroup, AddRemoveGetLock)
{
    //door without lock
    CHECK_EQUAL(nullptr, door->getLock());
    CHECK_FALSE(door->isLocked());
    //add the lock
    CHECK(door->addObject(keylock));
    CHECK(door->isLocked());
    CHECK(door->setLocked(false));
    CHECK_FALSE(door->isLocked());
    CHECK(door->setLocked(true));
    CHECK(door->isLocked());
    CHECK_EQUAL(keylock, door->getLock());
    //remove the lock
    CHECK(door->removeObject(keylock));
    CHECK_EQUAL(nullptr, door->getLock());
    CHECK_FALSE(door->setLocked(true));
    //return back
    CHECK(door->addObject(keylock));
    //re-adding
    CHECK_FALSE(door->addObject(keylock));
    //add not lock
    Key key(5);
    CHECK_FALSE(door->addObject(&key));
}

TEST(DoorGroup, GetName)
{
    CHECK_EQUAL(Lbr::ObjDoor, door->getName());
}

TEST(DoorGroup, GetNameString)
{
    CHECK_EQUAL("door", door->getNameString());
}

TEST(DoorGroup, AddObject)
{
    Key key(4);
    CHECK_FALSE(door->addObject(&key));
    CHECK_EQUAL(nullptr, door->findObject(Action(Lbr::ActNone, Lbr::ObjKey)));
    CHECK_FALSE(door->removeObject(&key));
}
