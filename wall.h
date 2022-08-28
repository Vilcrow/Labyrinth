#ifndef WALL_H_SENTRY
#define WALL_H_SENTRY

#include "labyrinth.h"

class WallObject : public LabyrinthObject {
    Labyrinth::WallType type;
public:
    WallObject(Labyrinth::WallType tp);
    virtual ~WallObject() {}
    void setProperties() {}
};

#endif
