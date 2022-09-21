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
#include "key.h"

TEST_GROUP(KeyGroup)
{
    KeyObject *key;
    int number = 10;

    void setup()
    {
        key = new KeyObject(number);
    }
    void teardown()
    {
        delete key;
    }
};

TEST(KeyGroup, GetName)
{
    CHECK_EQUAL("key", key->getName());
}

TEST(KeyGroup, GetNumber)
{
    CHECK_EQUAL(number, key->getNumber());
}
