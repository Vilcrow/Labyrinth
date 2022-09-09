#include "room.h"

RoomObject::RoomObject(int num) : LabyrinthObject(Labyrinth::ObjectRoom)
                                , number(num)
{
    top = new WallObject();
    down = new WallObject();
    left = new WallObject();
    right = new WallObject();
}
//add object to corresponding wall
void RoomObject::addObject(Labyrinth::WallType wall, LabyrinthObject *obj)
{
    switch(wall) {
    case Labyrinth::WallTop:
        top->addObject(obj);
        break;
    case Labyrinth::WallDown:
        down->addObject(obj);
        break;
    case Labyrinth::WallLeft:
        left->addObject(obj);
        break;
    case Labyrinth::WallRight:
        right->addObject(obj);
        break;
    }
}

WallObject* RoomObject::getWall(Labyrinth::WallType type)
{
    switch(type) {
    case Labyrinth::WallTop:
        return top;
    case Labyrinth::WallDown:
        return down;
    case Labyrinth::WallLeft:
        return left;
    case Labyrinth::WallRight:
        return right;
    }
    return nullptr; //gived invalid type of wall
}

std::string RoomObject::handleAction(const Action& act)
{
    return "OK";
}
