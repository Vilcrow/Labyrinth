#ifndef PLAYER_H_SENTRY
#define PLAYER_H_SENTRY

#include <memory>
#include "backpack.h"
#include "labyrinth.h"
#include "room.h"

//singleton pattern
class Player {
    int roomNum;
    BackpackObject* backpack;
    std::shared_ptr<WallObject> curWall;
public:
    static Player* instance();
    int roomNumber() { return roomNum; }
    void roomNumber(int num) { roomNum = num; }
    void currentWall(std::shared_ptr<WallObject> wall) { curWall = wall; }
private:
    Player();
    ~Player() = delete;
    Player(Player& other) = delete;
    Player& operator=(Player& other) = delete;
protected:
    static Player *uniqueInstance;
};

#endif
