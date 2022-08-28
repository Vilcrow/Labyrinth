#ifndef ROOM_H_SENTRY
#define ROOM_H_SENTRY

#include <vector>
#include "labyrinth.h"

class RoomObject : public LabyrinthObject {
    int number;
    std::vector<LabyrinthObject> top;
    std::vector<LabyrinthObject> down;
    std::vector<LabyrinthObject> left;
    std::vector<LabyrinthObject> right;
public:
    RoomObject(int num);
    virtual ~RoomObject() {}
    void setProperties() override {}
    void addObject(Labyrinth::WallType wall, LabyrinthObject obj);
};

#endif
