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

#include "commands.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(CommandsGroup)
{
    void setup()
    {
        MemoryLeakWarningPlugin::saveAndDisableNewDeleteOverloads();
    }
    void teardown()
    {
        MemoryLeakWarningPlugin::restoreNewDeleteOverloads();
    }
};

TEST(CommandsGroup, NotNullptr)
{
    CHECK(COMMANDS);
}

TEST(CommandsGroup, CommandToActionWithEmptyInput)
{
    Action act = COMMANDS->cmdToAction("");
    CHECK_EQUAL(Lbr::ActNone, act.aType);
    CHECK_EQUAL(Lbr::ObjNone, act.oName);
    CHECK_EQUAL(Lbr::None, act.oType);
    CHECK_EQUAL(-1, act.number);
}

TEST(CommandsGroup, CommandToActionWithoutActionInInput)
{
    Action act = COMMANDS->cmdToAction("blablatrash door ea4 fs5 3");
    CHECK_EQUAL(Lbr::ActNone, act.aType);
    CHECK_EQUAL(Lbr::ObjDoor, act.oName);
    CHECK_EQUAL(Lbr::Container, act.oType);
    CHECK_EQUAL(3, act.number);
}

TEST(CommandsGroup, CommandToActionWithoutObjectInInput)
{
    Action act = COMMANDS->cmdToAction("inspect 8 blablatrash ea4 fs5");
    CHECK_EQUAL(Lbr::ObjNone, act.oName);
    CHECK_EQUAL(Lbr::None, act.oType);
}

TEST(CommandsGroup, CommandToActionWithoutNumberInInput)
{
    Action act = COMMANDS->cmdToAction("inspect blablatrash door ea4 fs5");
    CHECK_EQUAL(-1, act.number);
}

TEST(CommandsGroup, CommandToActionWithInvalidActionInInput)
{
    Action act = COMMANDS->cmdToAction("inspeect door");
    CHECK_EQUAL(Lbr::ActNone, act.aType);
}

TEST(CommandsGroup, CommandToActionWithInvalidObjectInInput)
{
    Action act = COMMANDS->cmdToAction("throw dooor");
    CHECK_EQUAL(Lbr::ObjNone, act.oName);
}

TEST(CommandsGroup, CommandToActionWithInvalidNumberInInput)
{
    Action act = COMMANDS->cmdToAction("throw -54");
    CHECK_EQUAL(-1, act.number);
}

TEST(CommandsGroup, CommandToActionWithFullInvalidInput)
{
    Action act = COMMANDS->cmdToAction("insperct blablatrash kdoor ea4 fs5");
    CHECK_EQUAL(Lbr::ActNone, act.aType);
    CHECK_EQUAL(Lbr::ObjNone, act.oName);
    CHECK_EQUAL(Lbr::None, act.oType);
    CHECK_EQUAL(-1, act.number);
}

TEST(CommandsGroup, CommandToActionWithFullInput)
{
    Action act = COMMANDS->cmdToAction("take key 4");
    CHECK_EQUAL(Lbr::ActTake, act.aType);
    CHECK_EQUAL(Lbr::ObjKey, act.oName);
    CHECK_EQUAL(Lbr::Object, act.oType);
    CHECK_EQUAL(4, act.number);
}
