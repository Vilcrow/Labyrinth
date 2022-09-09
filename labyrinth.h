#ifndef LABYRINTH_H_SENTRY
#define LABYRINTH_H_SENTRY

#include <string>

struct Action;

//Class namespace for various enums
class Labyrinth {
public:
    enum ActionType {
                     ActionNone,
                     ActionClose,
                     ActionOpen,
                     ActionInspect,
                     ActionTake,
                     ActionUse
    };
    enum ObjectType {
                     ObjectNone,
                     ObjectBattery,
                     ObjectDoor,
                     ObjectFlashlight,
                     ObjectKey,
                     ObjectRoom,
                     ObjectSheet,
                     ObjectWall
    };
    enum WallType   {
                     WallTop,
                     WallDown,
                     WallLeft,
                     WallRight
    };

    Labyrinth() = delete;
    ~Labyrinth() = delete;
};
//parent of all other object classes
class LabyrinthObject {
    Labyrinth::ObjectType type;
public:
    LabyrinthObject(Labyrinth::ObjectType t) : type(t) {}
    virtual ~LabyrinthObject() {}
    Labyrinth::ObjectType getType() const { return type; }
    virtual std::string handleAction(const Action& act) = 0;
};

struct Action {
    Action(Labyrinth::ActionType act, Labyrinth::ObjectType obj)
               : aType(act), oType(obj) {}
    Labyrinth::ActionType aType;
    Labyrinth::ObjectType oType;
};

#endif
