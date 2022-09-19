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

#ifndef COMMANDS_H_SENTRY
#define COMMANDS_H_SENTRY

#include <string>
#include <map>
#include <memory>
#include <vector>
#include "labyrinth.h"

#define COMMANDS Commands::instance()

//Class which holds all commands for the command line
//(singleton pattern)
class Commands {
public:
    static Commands* instance();
    Action cmdToAction(const std::string &cmd);
    static std::string objectsList(const std::vector<LabyrinthObject*>& vec);
private:
    Commands();
    ~Commands() = delete;
    Commands(Commands&) = delete;
    Commands& operator=(Commands&) = delete;
    
    std::map<std::string, Labyrinth::ActionType> actionCommands;
    std::map<std::string, Labyrinth::ObjectType> objectCommands;
protected:
    static Commands *uniqueInstance;
};

#endif
