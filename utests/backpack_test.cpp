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
#include "labyrinth.h"
#include "backpack.h"
#include "key.h"
#include "sheet.h"

TEST_GROUP(BackpackGroup)
{
    Backpack *backpack = nullptr;
    Key *key = nullptr;
    int key_num = 4;
    Sheet *sheet = nullptr;
    void setup()
    {
        backpack = new Backpack();
        key = new Key(key_num);
        sheet = new Sheet("Backpack test");
    }
    void teardown()
    {
        delete backpack;
        delete key;
        delete sheet;
    }
};

TEST(BackpackGroup, EmptyAfterCreation)
{
    CHECK_EQUAL(6, backpack->getCapacity());
}

TEST(BackpackGroup, AddAndRemoveObject)
{
    CHECK_EQUAL(6, backpack->getCapacity());
    CHECK(backpack->addObject(key));
    CHECK_EQUAL(5, backpack->getCapacity());
    CHECK(backpack->addObject(sheet));
    CHECK_EQUAL(4, backpack->getCapacity());
}

TEST(BackpackGroup, CannotAddObjectTwice)
{
    CHECK(backpack->addObject(key));
    CHECK_FALSE(backpack->addObject(key));
}

TEST(BackpackGroup, GetCapacity)
{
    CHECK_EQUAL(6, backpack->getCapacity());
    CHECK(backpack->addObject(key));
    CHECK_EQUAL(5, backpack->getCapacity());
}

TEST(BackpackGroup, FindObject)
{
    Action act(Lbr::ActNone, Lbr::ObjKey);
    //find by name
    CHECK_EQUAL(nullptr, backpack->findObject(act));
    CHECK(backpack->addObject(key));
    CHECK_EQUAL(key, backpack->findObject(act));
    act.oName = Lbr::ObjSheet;
    CHECK_EQUAL(nullptr, backpack->findObject(act));
    CHECK(backpack->addObject(sheet));
    CHECK_EQUAL(sheet, backpack->findObject(act));
    //find by number
    act.oName = Lbr::ObjNone;
    act.number = 0;
    CHECK_EQUAL(key, backpack->findObject(act));
    act.number = 1;
    CHECK_EQUAL(sheet, backpack->findObject(act));
    act.number = 4;
    CHECK_EQUAL(nullptr, backpack->findObject(act));
}

TEST(BackpackGroup, FindKey)
{
    CHECK(backpack->addObject(key));
    CHECK_EQUAL(key, backpack->findKey(key_num));
    CHECK_EQUAL(nullptr, backpack->findKey(key_num+5));
}

TEST(BackpackGroup, GetName)
{
    CHECK_EQUAL(Lbr::ObjBackpack, backpack->getName());
}

TEST(BackpackGroup, GetNameString)
{
    CHECK_EQUAL("backpack", backpack->getNameString());
}

TEST(BackpackGroup, GetObjects)
{
    CHECK(backpack->addObject(key));
    CHECK_EQUAL(key, backpack->getObjects()[0]);
}
