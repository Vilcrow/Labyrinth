#ifndef PLAYER_H_SENTRY
#define PLAYER_H_SENTRY

#include <memory>
#include "labyrinth.h"
#include "room.h"

class Player {
    ObjectRoom *curRoom;
    unique_ptr<ObjectBackPack> backpack;
public:
    Player() {}
    ~Player() {}
};

#endif
