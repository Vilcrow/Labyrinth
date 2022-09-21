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
#include "room.h"
#include "key.h"

TEST_GROUP(RoomGroup)
{
    RoomObject *room;
    KeyObject *key;
    DoorObject *door;

    int room_num = 10;
    int kd_num = 5; //number of key and door

    Action act;

    void setup()
    {
        room = new RoomObject(room_num);
        key = new KeyObject(kd_num);
        door = new DoorObject(kd_num);
    }
    void teardown()
    {
        delete room;
        delete key;
        delete door;
    }
};

TEST(RoomGroup, AddObject)
{
    room->addObject(Labyrinth::WallTop, door);
    room->addObject(Labyrinth::WallTop, key);
    CHECK_EQUAL(door, room->findDoor(kd_num));
    WallContainer *wall = room->getCurrentWall();
    CHECK_EQUAL(wall->getObjects()[0], door);
    CHECK_EQUAL(wall->getObjects()[1], key);
}

TEST(RoomGroup, SetAndGetCurrentWall)
{
    //default type
    CHECK_EQUAL(Labyrinth::WallTop, room->getCurrentWallType());
    //change current wall
    room->setCurrentWall(Labyrinth::WallDown);
    CHECK_EQUAL(Labyrinth::WallDown, room->getCurrentWallType());
}

TEST(RoomGroup, GetNumber)
{
    CHECK_EQUAL(room_num, room->getNumber());
}

TEST(RoomGroup, GetName)
{
    CHECK_EQUAL("room", room->getName());
}

TEST(RoomGroup, FindDoor)
{
    room->addObject(Labyrinth::WallLeft, door);
    CHECK_EQUAL(door, room->findDoor(kd_num));
}
