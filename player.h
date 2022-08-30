#ifndef PLAYER_H_SENTRY
#define PLAYER_H_SENTRY

#include <memory>
#include "backpack.h"
#include "labyrinth.h"
#include "room.h"

//singleton pattern
class Player {
    int roomNumber;
    BackpackObject* backpack;
    WallObject* curWall;
public:
    static Player* instance();
private:
    Player();
    ~Player() = delete;
    Player(Player& other) = delete;
    Player& operator=(Player& other) = delete;
protected:
    static Player *uniqueInstance;
};

#endif
