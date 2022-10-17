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

#include "room.h"
#include "key.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(RoomGroup)
{
    Room *room = nullptr;
    Door *door = nullptr;
    int room_num = 31;
    int door_num = 32;
    void setup()
    {
        room = new Room(room_num);
        door = new Door(door_num);
    }
    void teardown()
    {
        delete room;
        delete door;
    }
};

TEST(RoomGroup, AddFindRemoveContainer)
{
    CHECK(room->addContainer(Lbr::WallLeft, door));
    Action act(Lbr::ActNone, Lbr::ObjDoor);
    CHECK_EQUAL(door,
                room->getWall(Lbr::WallLeft)->findContainer(act));
    CHECK(room->removeContainer(Lbr::WallLeft, door));
}

TEST(RoomGroup, GetWall)
{
    CHECK_FALSE(nullptr == room->getWall(Lbr::WallTop));
    CHECK_FALSE(nullptr == room->getWall(Lbr::WallDown));
    CHECK_FALSE(nullptr == room->getWall(Lbr::WallLeft));
    CHECK_FALSE(nullptr == room->getWall(Lbr::WallRight));
}

TEST(RoomGroup, GetNumber)
{
    CHECK_EQUAL(room_num, room->getNumber());
}

TEST(RoomGroup, GetName)
{
    CHECK_EQUAL(Lbr::ObjRoom, room->getName());
}

TEST(RoomGroup, GetNameString)
{
    CHECK_EQUAL("room", room->getNameString());
}

TEST(RoomGroup, FindDoor)
{
    CHECK(room->addContainer(Lbr::WallLeft, door));
    CHECK_EQUAL(door, room->findDoor(door_num));
    //for the correct operation of the cassette destructor
    CHECK(room->removeContainer(Lbr::WallLeft, door));
}
