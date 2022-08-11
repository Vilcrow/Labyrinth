#include "door.h"

DoorObject::DoorObject(Labyrinth::ObjectType type,
                       int num, bool opnd) :
                       LabyrinthObject(type), number(num), opened(opnd)
{

}
