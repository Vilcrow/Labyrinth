#ifndef GAME_H_SENTRY
#define GAME_H_SENTRY

#include "backpack.h"
#include "commands.h"
#include "door.h"
#include "room.h"

//singleton pattern
class Game {
    int roomNumber;
    BackpackObject *backpack;
    Commands *commands;
    std::map<int, RoomObject*> gameMap; //all rooms
public:
    static Game* instance();
    void run();
private:
    Game();
    ~Game() = delete;
    Game(Game&) = delete;
    Game& operator=(Game&) = delete;
    void generateMap();
    std::string handleAction(const Action& act);
protected:
    static Game *uniqueInstance;
};

#endif
