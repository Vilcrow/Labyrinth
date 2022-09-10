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
                     , { "open"    , Labyrinth::ActionOpen    }
                     };
    objectCommands = { { "battery"    , Labyrinth::ObjectBattery    }
                     , { "door"       , Labyrinth::ObjectDoor       }
                     , { "flashlight" , Labyrinth::ObjectFlashlight }
                     , { "key"        , Labyrinth::ObjectKey        }
                     , { "room"       , Labyrinth::ObjectRoom       }
                     , { "sheet"      , Labyrinth::ObjectSheet      }
                     , { "wall"       , Labyrinth::ObjectWall       }
                     };
}

Commands* Commands::instance()
{
    if(!uniqueInstance)
        uniqueInstance = new Commands();
    return uniqueInstance;
}

std::shared_ptr<Action> Commands::cmdToAction(const std::string &cmd)
{
    std::shared_ptr<Action> action =
        std::make_shared<Action>(Labyrinth::ActionNone,
                                 Labyrinth::ObjectNone);
    if(cmd.empty())
        return action;
    std::string lowcmd = cmd;
    for(auto& c : lowcmd) {
        c = std::tolower(c);
    }
    std::set<std::string> words;
    auto end = lowcmd.find_first_of(" \t\n");
    decltype(end) start = 0;
    while(end != std::string::npos) { //extract all unique words from input
        if(end > start) {
            std::string token = lowcmd.substr(start, end - start);
            words.insert(token);
        }
        start = end + 1;
        end = lowcmd.find_first_of(" \t\n", start);
    }
    if(start != lowcmd.size()) {
        std::string token = lowcmd.substr(start);
        words.insert(token);
    }
    for(auto& a : words) {
        if(actionCommands.count(a)) {
            action->aType = actionCommands[a];
            break;
        }
    }
    for(auto& o : words) {
        if(objectCommands.count(o)) {
            action->oType = objectCommands[o];
            break;
        }
    }
    return action;
}
