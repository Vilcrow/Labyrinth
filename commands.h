#ifndef COMMANDS_H_SENTRY
#define COMMANDS_H_SENTRY

#include <string>
#include "labyrinth.h"

//Class which holds all commands for the command line
class Commands {
    Labyrinth::ActionType cmdToAction(const std::string &cmd);
public:
    Commands();
    ~Commands() = delete;
    Commands(Commands&) = delete;
    Commands& operator=(Commands&) = delete;
};

#endif
