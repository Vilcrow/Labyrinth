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
#include <string>

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
    std::string input = "";
    Action act = COMMANDS->cmdToAction(input);
    CHECK_EQUAL(act.aType, Labyrinth::ActionNone);
    CHECK_EQUAL(act.oType, Labyrinth::ObjectNone);
    CHECK_EQUAL(act.number, -1);
}

TEST(CommandsGroup, CommandToActionWithoutActionInInput)
{
    std::string input = "key 2";
    Action act = COMMANDS->cmdToAction(input);
    CHECK_EQUAL(act.aType, Labyrinth::ActionNone);
    CHECK_EQUAL(act.oType, Labyrinth::ObjectKey);
    CHECK_EQUAL(act.number, 2);
}

TEST(CommandsGroup, CommandToActionWithoutObjectInInput)
{
    std::string input = "take 2";
    Action act = COMMANDS->cmdToAction(input);
    CHECK_EQUAL(act.aType, Labyrinth::ActionTake);
    CHECK_EQUAL(act.oType, Labyrinth::ObjectNone);
    CHECK_EQUAL(act.number, 2);
}

TEST(CommandsGroup, CommandToActionWithoutNumberInInput)
{
    std::string input = "take key";
    Action act = COMMANDS->cmdToAction(input);
    CHECK_EQUAL(act.aType, Labyrinth::ActionTake);
    CHECK_EQUAL(act.oType, Labyrinth::ObjectKey);
    CHECK_EQUAL(act.number, -1);
}

TEST(CommandsGroup, CommandToActionWithInvalidActionInInput)
{
    std::string input = "takkkke sheet 2";
    Action act = COMMANDS->cmdToAction(input);
    CHECK_EQUAL(act.aType, Labyrinth::ActionNone);
    CHECK_EQUAL(act.oType, Labyrinth::ObjectSheet);
    CHECK_EQUAL(act.number, 2);
}

TEST(CommandsGroup, CommandToActionWithInvalidObjectInInput)
{
    std::string input = "take keeeey 5";
    Action act = COMMANDS->cmdToAction(input);
    CHECK_EQUAL(act.aType, Labyrinth::ActionTake);
    CHECK_EQUAL(act.oType, Labyrinth::ObjectNone);
    CHECK_EQUAL(act.number, 5);
}

TEST(CommandsGroup, CommandToActionWithInvalidNumberInInput)
{
    std::string input = "take key 2df";
    Action act = COMMANDS->cmdToAction(input);
    CHECK_EQUAL(act.aType, Labyrinth::ActionTake);
    CHECK_EQUAL(act.oType, Labyrinth::ObjectKey);
    CHECK_EQUAL(act.number, -1);
}

TEST(CommandsGroup, CommandToActionWithFullInvalidInput)
{
    std::string input = "takkke keeeey 2df";
    Action act = COMMANDS->cmdToAction(input);
    CHECK_EQUAL(act.aType, Labyrinth::ActionNone);
    CHECK_EQUAL(act.oType, Labyrinth::ObjectNone);
    CHECK_EQUAL(act.number, -1);
}

TEST(CommandsGroup, CommandToActionWithFullInput)
{
    std::string input = "take key 2";
    Action act = COMMANDS->cmdToAction(input);
    CHECK_EQUAL(act.aType, Labyrinth::ActionTake);
    CHECK_EQUAL(act.oType, Labyrinth::ObjectKey);
    CHECK_EQUAL(act.number, 2);
}
