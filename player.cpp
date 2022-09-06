#include "player.h"

Player* Player::uniqueInstance = nullptr;

Player::Player()
{
    roomNum = 0; //start of the game
    backpack = BackpackObject::instance();
    curWall = nullptr;
}

Player* Player::instance()
{
    if(!uniqueInstance)
        uniqueInstance = new Player();
    return uniqueInstance;
}
