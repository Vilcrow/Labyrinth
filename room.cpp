#include "room.h"

RoomObject::RoomObject() : LabyrinthObject(Labyrinth::ObjectRoom)
{
    top = new WallObject();
    down = new WallObject();
    left = new WallObject();
    right = new WallObject();
    currentWall = top;
    wallType = Labyrinth::WallTop;
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

void RoomObject::setCurrentWall(Labyrinth::WallType type)
{
    switch(type) {
    case Labyrinth::WallTop:
        currentWall = top;
    case Labyrinth::WallDown:
        currentWall = down;
    case Labyrinth::WallLeft:
        currentWall = left;
    case Labyrinth::WallRight:
        currentWall = right;
    }
    wallType = type;
}

std::string RoomObject::handleAction(const Action& act)
{
    return "OK";
}

RoomObject::~RoomObject()
{
    delete top;
    delete down;
    delete left;
    delete right;
}
