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

#include <algorithm>
#include <iostream>
#include <set>
#include "commands.h"

Commands* Commands::uniqueInstance = nullptr;

Commands::Commands()
{
    actionCommands = { { "close"   , Labyrinth::ActionClose   }
                     , { "inspect" , Labyrinth::ActionInspect }
                     , { "take"    , Labyrinth::ActionTake    }
                     , { "use"     , Labyrinth::ActionTake    }
                     , { "push"    , Labyrinth::ActionPush    }
                     , { "pull"    , Labyrinth::ActionPull    }
                     , { "throw"   , Labyrinth::ActionThrow   }
                     , { "open"    , Labyrinth::ActionOpen    }
                     , { "enter"   , Labyrinth::ActionEnter   }
                     };
    objectCommands = { { "battery"    , Labyrinth::ObjectBattery    }
                     , { "backpack"   , Labyrinth::ObjectBackpack   }
                     , { "door"       , Labyrinth::ObjectDoor       }
                     , { "flashlight" , Labyrinth::ObjectFlashlight }
                     , { "key"        , Labyrinth::ObjectKey        }
                     , { "room"       , Labyrinth::ObjectRoom       }
                     , { "sheet"      , Labyrinth::ObjectSheet      }
                     , { "wall"       , Labyrinth::ObjectWall       }
                     , { "top"        , Labyrinth::ObjectWallTop    }
                     , { "down"       , Labyrinth::ObjectWallDown   }
                     , { "left"       , Labyrinth::ObjectWallLeft   }
                     , { "right"      , Labyrinth::ObjectWallRight  }
                     , { "watch"      , Labyrinth::ObjectWatch      }
                     };
}

Commands* Commands::instance()
{
    if(!uniqueInstance)
        uniqueInstance = new Commands();
    return uniqueInstance;
}

Action Commands::cmdToAction(const std::string &cmd)
{
    Action action;
    if(cmd.empty())
        return action;
    std::string lowcmd = cmd;
    for(auto& c : lowcmd) {
        c = std::tolower(c);
    }
    std::set<std::string> words;
    auto end = lowcmd.find_first_of(" \t");
    decltype(end) start = 0;
    while(end != std::string::npos) { //extract all unique words from input
        if(end > start) {
            std::string token = lowcmd.substr(start, end - start);
            words.insert(token);
        }
        start = end + 1;
        end = lowcmd.find_first_of(" \t", start);
    }
    if(start != lowcmd.size()) {  //extract last word
        std::string token = lowcmd.substr(start);
        words.insert(token);
    }
    for(auto a : words) {
        if(actionCommands.count(a)) {
            action.aType = actionCommands[a];
            break;
        }
    }
    for(auto o : words) {
        if(objectCommands.count(o)) {
            action.oType = objectCommands[o];
            break;
        }
    }
    for(auto o : words) {
        if(std::all_of(o.begin(), o.end(), ::isdigit))
        {
            action.number = std::stoi(o);
            break;
        }
    }
    return action;
}

std::string Commands::objectsList(const std::vector<LabyrinthObject*>& vec)
{
    std::string result;
    if(vec.empty())
        result = "nothing.";
    else {
        int number = 0;
        for(auto o : vec) {
            result += o->getName();
            result += "(" + std::to_string(number) + ")";
            result += ", ";
            number++;
        }
        result.pop_back();
        result[result.size()-1] = '.';
    }
    return result;
}

void Commands::addCommand(const std::string& cmd)
{
    if(cmd.empty())
        return;
    history.push_back(cmd);
}
