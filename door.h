#ifndef DOOR_H_SENTRY
#define DOOR_H_SENTRY

#include "labyrinth.h"

class DoorObject : public LabyrinthObject {
    int number;
    bool opened;
public:
    DoorObject(int num, bool opnd = false);
    virtual ~DoorObject() {}
    void setProperties(bool opnd) { opened = opnd; }
    int getNumber() const { return number; }
    bool isOpen() const { return opened; }
};

#endif
