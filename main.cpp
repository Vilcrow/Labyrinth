#include <iostream>
#include "backpack.h"
#include "door.h"
#include "labyrinth.h"
#include "room.h"
#include "player.h"

int main(int argc, char **argv)
{
    //tests
    Player *player = Player::instance();
    RoomObject *room = new RoomObject(1);
    room->addWall(Labyrinth::WallTop, std::make_shared<WallObject>());
    room->addWall(Labyrinth::WallDown, std::make_shared<WallObject>());
    room->addWall(Labyrinth::WallLeft, std::make_shared<WallObject>());
    room->addWall(Labyrinth::WallRight, std::make_shared<WallObject>());
    //player->setCurrentWall();
    player->setRoomNumber(room->getNumber());
    KeyObject key(1);
    DoorObject door(2);
    room->addObject(Labyrinth::WallTop, key);
    room->addObject(Labyrinth::WallTop, door);
    return 0;
}
