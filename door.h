#ifndef DOOR_H_SENTRY
#define DOOR_H_SENTRY

#include "labyrinth.h"

class KeyObject;

class DoorObject : public LabyrinthObject {
    int number;
    bool opened;
public:
    DoorObject(int num, bool opnd = false);
    virtual ~DoorObject() {}
    int getNumber() const { return number; }
    bool isOpened() const { return opened; }
    bool open(const KeyObject& key);
    std::string handleAction(const Action& act) override;
    std::string getName() const override { return "door"; }
};

class KeyObject : public LabyrinthObject {
    int number;
public:
    KeyObject(int num) : LabyrinthObject(Labyrinth::ObjectKey), number(num) {}
    ~KeyObject() = default;
    int getNumber() const { return number; }
    std::string handleAction(const Action& act) override;
    std::string getName() const override { return "key"; }
};

#endif
