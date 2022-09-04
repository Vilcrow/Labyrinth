#ifndef COMMANDS_H_SENTRY
#define COMMANDS_H_SENTRY

#include <string>
#include "labyrinth.h"

//Class which holds all commands for the command line
//singleton pattern
class Commands {
    Labyrinth::ActionType cmdToAction(const std::string &cmd);
public:
    static Commands *instance();
private:
    Commands();
    ~Commands() = delete;
    Commands(Commands&) = delete;
    Commands& operator=(Commands&) = delete;
protected:
    static Commands *uniqueInstance;
};

#endif
