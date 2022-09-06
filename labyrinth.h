#ifndef LABYRINTH_H_SENTRY
#define LABYRINTH_H_SENTRY

//Class namespace for various enums
class Labyrinth {
public:
    enum ActionType {
                     ActionNone,
                     ActionCloseDoor,
                     ActionOpenDoor,
                     ActionViewDoor
    };
    enum ObjectType {
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
};
//parent of all other object classes
class LabyrinthObject {
    Labyrinth::ObjectType objectType;
public:
    LabyrinthObject(Labyrinth::ObjectType type) : objectType(type) {}
    virtual ~LabyrinthObject() {}
    Labyrinth::ObjectType type() const { return objectType; }
};

#endif
