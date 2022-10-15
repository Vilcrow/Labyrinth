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

#ifndef GAME_H_SENTRY
#define GAME_H_SENTRY

#include "backpack.h"
#include "battery.h"
#include "cassette.h"
#include "commands.h"
#include "door.h"
#include "inscription.h"
#include "player.h"
#include "room.h"
#include "safe.h"
#include "sheet.h"
#include "shelf.h"
#include "watch.h"

class Game {
public:
    Game();
    ~Game();
    void run();
    std::string save();
private:
    enum { roomCount = 81 };
    int roomNumber;
    Lbr::WallType curWallType;
    LbrContainer *curContainer;
    Backpack *backpack;
    std::map<int, Room*> gameMap; //all rooms

    Game(Game&) = delete;
    Game& operator=(Game&) = delete;
    void generateMap();
    std::string handleActionWithObject(Action act, LbrObject *obj);
    std::string handleActionWithContainer(Action act);
    std::string getContext() const;
    std::string ActionWithBackpack(Lbr::ActType aType);
    std::string ActionWithBattery(Lbr::ActType aType, Battery *battery);
    std::string ActionWithCassette(Lbr::ActType aType, Cassette *cassette);
    std::string ActionWithDoor(Lbr::ActType aType);
    std::string ActionWithInscription(Lbr::ActType aType, Inscription *key);
    std::string ActionWithKey(Lbr::ActType aType, Key *key);
    std::string ActionWithLock(Lbr::ActType aType, LbrLock *lock);
    std::string ActionWithPlayer(Lbr::ActType aType);
    std::string ActionWithRoom(Lbr::ActType aType, Room *room);
    std::string ActionWithSafe(Lbr::ActType aType);
    std::string ActionWithSheet(Lbr::ActType aType, Sheet *sheet);
    std::string ActionWithShelf(Lbr::ActType aType);
    std::string ActionWithWall(Lbr::ActType aType);
    std::string ActionWithWatch(Lbr::ActType aType, Watch *watch);
    std::string OpenLock(LbrLock *lock);
    std::string ActionTakeObject(LbrObject *obj);
    std::string ActionThrowObject(LbrObject *obj);
};

#endif
