#include <iostream>
#include "commands.h"

Commands* Commands::uniqueInstance = nullptr;

Commands::Commands()
{
    //std::initializer_list<>
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

std::shared_ptr<CommandItem> Commands::cmdToAction(const std::string &cmd)
{
    return std::make_shared<CommandItem>(Labyrinth::ActionNone,
            Labyrinth::ObjectNone);
}
