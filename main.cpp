#include <iostream>
#include "backpack.h"
#include "door.h"
#include "labyrinth.h"
#include "room.h"
#include "player.h"
#include "commands.h"

int main(int argc, char **argv)
{
    //tests
    Player *player = Player::instance();
    Commands *commands = Commands::instance();
    RoomObject *room = new RoomObject(1);
    room->wall(Labyrinth::WallTop, std::make_shared<WallObject>());
    room->wall(Labyrinth::WallDown, std::make_shared<WallObject>());
    room->wall(Labyrinth::WallLeft, std::make_shared<WallObject>());
    room->wall(Labyrinth::WallRight, std::make_shared<WallObject>());
    player->currentWall(room->wall(Labyrinth::WallTop));
    player->roomNumber(room->number());
    KeyObject key(2);
    DoorObject door(2);
    room->add(Labyrinth::WallTop, key);
    room->add(Labyrinth::WallTop, door);
    room->add(Labyrinth::WallTop, door);
    room->add(Labyrinth::WallTop, door);
    std::cout << door.action(Labyrinth::ActionInspect) << std::endl;
    return 0;
}
