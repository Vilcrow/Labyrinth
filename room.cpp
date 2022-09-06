#include "room.h"

RoomObject::RoomObject(int num) : LabyrinthObject(Labyrinth::ObjectRoom)
                                , nmbr(num)
{
    top = nullptr;
    down = nullptr;
    left = nullptr;
    right = nullptr;
}
//add object to corresponding wall
void RoomObject::add(Labyrinth::WallType wall, LabyrinthObject obj)
{
    switch(wall) {
    case Labyrinth::WallTop:
        top->add(obj);
        break;
    case Labyrinth::WallDown:
        down->add(obj);
        break;
    case Labyrinth::WallLeft:
        left->add(obj);
        break;
    case Labyrinth::WallRight:
        right->add(obj);
        break;
    }
}


void RoomObject::wall(Labyrinth::WallType type,
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

std::shared_ptr<WallObject> RoomObject::wall(Labyrinth::WallType type)
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
