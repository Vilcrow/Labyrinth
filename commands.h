#ifndef COMMANDS_H_SENTRY
#define COMMANDS_H_SENTRY

#include <string>
#include <map>
#include <memory>
#include "labyrinth.h"

//Class which holds all commands for the command line
//singleton pattern
class Commands {
public:
    static Commands* instance();
    std::shared_ptr<Action> cmdToAction(const std::string &cmd);
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
