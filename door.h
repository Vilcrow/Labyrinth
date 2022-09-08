#ifndef DOOR_H_SENTRY
#define DOOR_H_SENTRY

#include "labyrinth.h"

class KeyObject;

class DoorObject : public LabyrinthObject {
    int nmbr;
    bool opened;
public:
    DoorObject(int num, bool opnd = false);
    virtual ~DoorObject() {}
    int number() const { return nmbr; }
    bool isOpened() const { return opened; }
    bool open(const KeyObject& key);
    const std::string action(Labyrinth::ActionType type);
};

class KeyObject : public LabyrinthObject {
    int nmbr;
public:
    KeyObject(int num) : LabyrinthObject(Labyrinth::ObjectKey), nmbr(num) {}
    ~KeyObject() = default;
    int number() const { return nmbr; }
    const std::string& action(Labyrinth::ActionType type);
};

#endif
