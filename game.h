#ifndef GAME_H_SENTRY
#define GAME_H_SENTRY

#include "player.h"
#include "commands.h"
#include "door.h"
#include "room.h"

//singleton pattern
class Game {
    Player *player;
    Commands *commands;
    //all rooms
    std::map<int, RoomObject*> gameMap;
public:
    static Game* instance();
    void run();
private:
    Game();
    ~Game() = delete;
    Game(Game&) = delete;
    Game& operator=(Game&) = delete;
    void generateMap();

protected:
    static Game *uniqueInstance;
};

#endif
