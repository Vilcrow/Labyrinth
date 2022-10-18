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
#include "digitallock.h"

TEST_GROUP(DigitalLockGroup)
{
    DigitalLock *digitallock = nullptr;
    int code = 1242;
    void setup()
    {
        digitallock = new DigitalLock(code);
    }
    void teardown()
    {
        delete digitallock;
    }
};

TEST(DigitalLockGroup, GetName)
{
    CHECK_EQUAL(Lbr::ObjLock, digitallock->getName());
}

TEST(DigitalLockGroup, GetType)
{
    CHECK_EQUAL(Lbr::LockDigital, digitallock->getType());
}

TEST(DigitalLockGroup, GetNameString)
{
    CHECK_EQUAL("digital lock", digitallock->getNameString());
}

TEST(DigitalLockGroup, GetCode)
{
    CHECK_EQUAL(code, digitallock->getCode());
}

TEST(DigitalLockGroup, OpenLock)
{
    CHECK(digitallock->openLock(code));
    CHECK_FALSE(digitallock->openLock(code+1));
}
