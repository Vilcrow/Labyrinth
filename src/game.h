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
#include "commands.h"
#include "door.h"
#include "inscription.h"
#include "room.h"
#include "sheet.h"
#include "watch.h"

class Game {
    int roomNumber;
    BackpackContainer *backpack;
    LabyrinthContainer *curContainer;
    std::map<int, RoomObject*> gameMap; //all rooms
public:
    Game();
    ~Game() = delete;
    void run();
    bool save();
private:
    Game(Game&) = delete;
    Game& operator=(Game&) = delete;
    void generateMap();
    std::string handleAction(Action act, LabyrinthObject *obj);
    std::string ActionWithBackpack(Labyrinth::ActionType aType);
    std::string ActionWithBattery(Labyrinth::ActionType aType,
                                  BatteryObject *battery);
    std::string ActionWithDoor(Labyrinth::ActionType aType, DoorObject *door);
    std::string ActionWithInscription(Labyrinth::ActionType aType,
                                      InscriptionObject *key);
    std::string ActionWithKey(Labyrinth::ActionType aType, KeyObject *key);
    std::string ActionWithRoom(Labyrinth::ActionType aType, RoomObject *room);
    std::string ActionWithSheet(Labyrinth::ActionType aType, SheetObject *sheet);
    std::string ActionWithWall(Labyrinth::ActionType aType);
    std::string ActionWithWatch(Labyrinth::ActionType aType, WatchObject *watch);
};

#endif
