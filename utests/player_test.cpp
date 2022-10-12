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
#include "player.h"
#include "cassette.h"
#include "key.h"

TEST_GROUP(PlayerGroup)
{
    Player *player = nullptr;
    const char *record = "Cassette test.";
    Cassette *cassette = nullptr;
    int player_num = 5;
    void setup()
    {
        player = new Player();
        cassette = new Cassette(record);
    }
    void teardown()
    {
        delete player;
        delete cassette;
    }
};

TEST(PlayerGroup, AddRemoveGetCassette)
{
    //empty player
    CHECK_EQUAL(nullptr, player->getCassette());
    //add cassette
    CHECK(player->addObject(cassette));
    //re-adding
    CHECK_FALSE(player->addObject(cassette));
    CHECK_EQUAL(cassette, player->getCassette());
    CHECK(player->removeObject(cassette));
    CHECK_EQUAL(nullptr, player->getCassette());
    //add not cassette
    Key key(2); 
    CHECK_FALSE(player->addObject(&key));
    CHECK_EQUAL(nullptr, player->getCassette());
}

TEST(PlayerGroup, GetRecord)
{
    CHECK(player->addObject(cassette));
    CHECK_EQUAL(record, player->getRecord());
}

TEST(PlayerGroup, GetName)
{
    CHECK_EQUAL(Lbr::ObjPlayer, player->getName());
}

TEST(PlayerGroup, GetNameString)
{
    CHECK_EQUAL("player", player->getNameString());
}
