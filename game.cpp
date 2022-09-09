#include "game.h"
#include "commands.h"
#include "player.h"

Game* Game::uniqueInstance = nullptr;

Game::Game()
{
    Player *player = Player::instance();
    Commands *commands = Commands::instance();
    generateMap();
}

Game* Game::instance()
{
    if(!uniqueInstance)
        uniqueInstance = new Game();
    return uniqueInstance;
}

void Game::run()
{

}

void Game::generateMap()
{
    //draft
    RoomObject *room = new RoomObject(1);
    KeyObject *key = new KeyObject(2);
    DoorObject *door = new DoorObject(2);
    room->addObject(Labyrinth::WallTop, key);
    room->addObject(Labyrinth::WallTop, door);
    room->addObject(Labyrinth::WallTop, door);
    room->addObject(Labyrinth::WallTop, door);
    gameMap[room->getNumber()] = room;
}
