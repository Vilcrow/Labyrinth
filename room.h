#ifndef ROOM_H_SENTRY
#define ROOM_H_SENTRY

#include <memory>
#include "labyrinth.h"
#include "wall.h"

class RoomObject : public LabyrinthObject {
    int number;
    WallObject* top;
    WallObject* down;
    WallObject* left;
    WallObject* right;
public:
    RoomObject(int num);
    virtual ~RoomObject() {}
    void addObject(Labyrinth::WallType wall, LabyrinthObject *obj);
    int getNumber() const { return number; }
    WallObject* getWall(Labyrinth::WallType type);
    std::string handleAction(const Action& act) override;
};

#endif
