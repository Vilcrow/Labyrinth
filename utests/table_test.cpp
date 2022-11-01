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
#include "table.h"
#include "key.h"

TEST_GROUP(TableGroup)
{
    Table *table = nullptr;
    Key *key = nullptr;
    int key_num = 5;
    void setup()
    {
        table = new Table();
        key = new Key(key_num);
    }
    void teardown()
    {
        delete table;
        delete key;
    }
};

TEST(TableGroup, AddRemoveFindObject)
{
    CHECK(table->addObject(key));
    CHECK_FALSE(table->addObject(key));
    CHECK_EQUAL(key, table->findObject(Action(Lbr::ActNone, Lbr::ObjKey)));
    CHECK(table->removeObject(key));
    CHECK_FALSE(table->removeObject(key));
}

TEST(TableGroup, GetName)
{
    CHECK_EQUAL(Lbr::ObjTable, table->getName());
}

TEST(TableGroup, GetNameString)
{
    CHECK_EQUAL("table", table->getNameString());
}
