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

#include "labyrinth.h"
#include <map>
#include <string>
#include <vector>

#define COMMANDS Commands::instance()

//Class which holds all commands for the command line
//(singleton pattern)
class Commands {
public:
    static Commands* instance();
    Action cmdToAction(const std::string &cmd);
    void addCommand(const std::string& cmd);
    const std::vector<std::string>& getHistory() const { return history; }
    void clearHistory() { history.clear(); }
private:
    std::map<std::string, Lbr::ActType> actionCommands;
    std::map<std::string, Lbr::ObjName> objectCommands;
    std::map<Lbr::ObjName, Lbr::ObjType> objectType;
    std::vector<std::string> history;

    Commands();
    ~Commands() = delete;
    Commands(Commands&) = delete;
    Commands& operator=(Commands&) = delete;
protected:
    static Commands *uniqueInstance;
};

#endif
