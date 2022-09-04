#include "commands.h"

Commands* Commands::uniqueInstance = nullptr;

Commands::Commands()
{

}

Commands* Commands::instance()
{
    if(!uniqueInstance)
        uniqueInstance = new Commands();
    return uniqueInstance;
}

Labyrinth::ActionType Commands::cmdToAction(const std::string &cmd)
{
	Labyrinth::ActionType type = Labyrinth::ActionNone;
    return type;
}
