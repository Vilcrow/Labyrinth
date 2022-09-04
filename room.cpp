#include "room.h"

RoomObject::RoomObject(int num) : LabyrinthObject(Labyrinth::ObjectRoom)
                                , number(num)
{
    top = nullptr;
    down = nullptr;
    left = nullptr;
    right = nullptr;
}

void RoomObject::addObject(Labyrinth::WallType wall, LabyrinthObject obj)
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


void RoomObject::addWall(Labyrinth::WallType type,
                         std::shared_ptr<WallObject> wall)
{
    switch(type) {
    case Labyrinth::WallTop:
        if(!top)
            top = wall;
        else {
            //need error handling
        }
        break;
    case Labyrinth::WallDown:
        if(!down)
            down = wall;
        else {
            //need error handling
        }
        break;
    case Labyrinth::WallLeft:
        if(!left)
            left = wall;
        else {
            //need error handling
        }
        break;
    case Labyrinth::WallRight:
        if(!right)
            right = wall;
        else {
            //need error handling
        }
    }
}
