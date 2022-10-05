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
#include <algorithm>
#include <iostream>
#include <set>

Commands* Commands::uniqueInstance = nullptr;

Commands::Commands()
{
    actionCommands = { { "close"   , Lbr::ActClose   }
                     , { "enter"   , Lbr::ActEnter   }
                     , { "inspect" , Lbr::ActInspect }
                     , { "open"    , Lbr::ActOpen    }
                     , { "pull"    , Lbr::ActPull    }
                     , { "push"    , Lbr::ActPush    }
                     , { "quit"    , Lbr::ActQuit    }
                     , { "read"    , Lbr::ActRead    }
                     , { "save"    , Lbr::ActSave    }
                     , { "take"    , Lbr::ActTake    }
                     , { "throw"   , Lbr::ActThrow   }
                     , { "use"     , Lbr::ActTake    }
                     };
    objectCommands = { { "battery"     , Lbr::ObjBattery,     }
                     , { "backpack"    , Lbr::ObjBackpack,    }
                     , { "door"        , Lbr::ObjDoor,        }
                     , { "down"        , Lbr::ObjWallDown,    }
                     , { "inscription" , Lbr::ObjInscription, }
                     , { "flashlight"  , Lbr::ObjFlashlight,  }
                     , { "key"         , Lbr::ObjKey,         }
                     , { "left"        , Lbr::ObjWallLeft,    }
                     , { "right"       , Lbr::ObjWallRight,   }
                     , { "room"        , Lbr::ObjRoom,        }
                     , { "sheet"       , Lbr::ObjSheet,       }
                     , { "shelf"       , Lbr::ObjShelf,       }
                     , { "top"         , Lbr::ObjWallTop,     }
                     , { "wall"        , Lbr::ObjWall,        }
                     , { "watch"       , Lbr::ObjWatch,       }
                     };
    objectType     = { { Lbr::ObjBattery,     Lbr::Object    }
                     , { Lbr::ObjBackpack,    Lbr::Container }
                     , { Lbr::ObjDoor,        Lbr::Container }
                     , { Lbr::ObjWallDown,    Lbr::None      }
                     , { Lbr::ObjInscription, Lbr::Object    }
                     , { Lbr::ObjFlashlight,  Lbr::Container }
                     , { Lbr::ObjKey,         Lbr::Object    }
                     , { Lbr::ObjWallLeft,    Lbr::None      }
                     , { Lbr::ObjWallRight,   Lbr::None      }
                     , { Lbr::ObjRoom,        Lbr::None      }
                     , { Lbr::ObjSheet,       Lbr::Object    }
                     , { Lbr::ObjShelf,       Lbr::Container }
                     , { Lbr::ObjWallTop,     Lbr::None      }
                     , { Lbr::ObjWall,        Lbr::None      }
                     , { Lbr::ObjWatch,       Lbr::Object    }
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
            action.oName = objectCommands[o];
            action.oType = objectType[action.oName];
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

void Commands::addCommand(const std::string& cmd)
{
    if(cmd.empty())
        return;
    history.push_back(cmd);
}
