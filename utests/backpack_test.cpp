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
#include "backpack.h"
#include "key.h"
#include "sheet.h"

TEST_GROUP(BackpackGroup)
{
    BackpackContainer *backpack;
    KeyObject *f_key;
    KeyObject *s_key;
    SheetObject *sheet;
    Action *act;
    int max_capacity = 6; //from BackpackContainer

    void setup()
    {
        backpack = new BackpackContainer();
        f_key = new KeyObject(10);
        s_key = new KeyObject(4);
        sheet = new SheetObject("Sheet");
        act = new Action(Labyrinth::ActionNone, Labyrinth::ObjectNone);
    }
    void teardown()
    {
        delete backpack;
        delete f_key;
        delete s_key;
        delete sheet;
        delete act;
    }
};

TEST(BackpackGroup, EmptyAfterCreation)
{
    CHECK_EQUAL(max_capacity, backpack->getCapacity());
}

TEST(BackpackGroup, AddObject)
{
    //empty backpack
    CHECK_EQUAL(max_capacity, backpack->getCapacity());
    CHECK(backpack->addObject(f_key));
    CHECK_EQUAL(max_capacity-1, backpack->getCapacity());
}

TEST(BackpackGroup, RemoveObject)
{
    CHECK_EQUAL(max_capacity, backpack->getCapacity());
    backpack->addObject(f_key);
    CHECK_EQUAL(max_capacity-1, backpack->getCapacity());
    CHECK(backpack->removeObject(f_key));
    CHECK_EQUAL(max_capacity, backpack->getCapacity());
}

TEST(BackpackGroup, CannotAddObjectToFullBackpack)
{
    //filling the backpack
    for(int i = 0; i < max_capacity; i++) {
        backpack->addObject(f_key);
    }
    //full backpack
    CHECK_EQUAL(0, backpack->getCapacity());
    CHECK_FALSE(backpack->addObject(f_key));
}

TEST(BackpackGroup, GetCapacity)
{
    CHECK_EQUAL(max_capacity, backpack->getCapacity());
}

TEST(BackpackGroup, FindObject)
{
    //the empty backpack
    CHECK_EQUAL(max_capacity, backpack->getCapacity());
    act->oType = Labyrinth::ObjectKey;
    CHECK_FALSE(backpack->findObject(*act));
    //add the first key
    backpack->addObject(f_key);
    act->oType = Labyrinth::ObjectKey;
    CHECK_EQUAL(backpack->findObject(*act), f_key);
    //the second key don't exist in the backpack
    CHECK_FALSE(backpack->findObject(*act) == s_key);
    //the sheet don't exist in the backpack
    act->oType = Labyrinth::ObjectSheet;
    CHECK_FALSE(backpack->findObject(*act));
    //add the sheet
    backpack->addObject(sheet);
    CHECK_EQUAL(backpack->findObject(*act), sheet);
    //add the second key
    backpack->addObject(s_key);
    act->oType = Labyrinth::ObjectKey;
    //still finding the first key
    CHECK_EQUAL(backpack->findObject(*act), f_key);
    //find by number
    act->number = 2;
    CHECK_EQUAL(backpack->findObject(*act), s_key);
}

TEST(BackpackGroup, GetName)
{
    CHECK_EQUAL("backpack", backpack->getName());
}

TEST(BackpackGroup, GetObjects)
{
    CHECK(backpack->getObjects().empty());
    backpack->addObject(f_key);
    backpack->addObject(s_key);
    CHECK_EQUAL(backpack->getObjects()[0], f_key);
    CHECK_EQUAL(backpack->getObjects()[1], s_key);
}
