#include "door.h"

DoorObject::DoorObject(int num, bool opnd)
                      : LabyrinthObject(Labyrinth::ObjectDoor)
                      , number(num), opened(opnd)
{

}
