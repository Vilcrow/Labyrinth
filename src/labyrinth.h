/*******************************************************************************
** vim:ts=4:sw=4:expandtab
**
** This file is part of the labyrinth project, a text adventure game
**
** Copyright (C) 2022 S.V.I 'Vilcrow', <vilcrow.net>
**
** LICENCE:
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
**
*******************************************************************************/

#ifndef LABYRINTH_H_SENTRY
#define LABYRINTH_H_SENTRY

#include <vector>
#include <string>

struct Action;

//Class namespace for various enums
class Lbr {
public:
    enum ActType {
                     ActNone,
                     ActClose,
                     ActEnter,
                     ActInspect,
                     ActOpen,
                     ActPush,
                     ActPull,
                     ActPut,
                     ActQuit,
                     ActPlay,
                     ActRead,
                     ActSave,
                     ActTake,
                     ActThrow = ActPut,
                     ActUse
    };
    enum ObjName {
                     ObjNone,
                     ObjBackpack,
                     ObjBattery,
                     ObjCassette,
                     ObjDoor,
                     ObjFlashlight,
                     ObjInscription,
                     ObjKey,
                     ObjLock,
                     ObjLockDigital,
                     ObjLockKey,
                     ObjPlayer,
                     ObjRoom,
                     ObjSafe,
                     ObjSheet,
                     ObjShelf,
                     ObjWall,
                     ObjWallTop,
                     ObjWallDown,
                     ObjWallLeft,
                     ObjWallRight,
                     ObjWatch
    };
    enum ObjType {
                     None,
                     Object,
                     Container
    };
    enum WallType {
                     WallNone,
                     WallDown,
                     WallLeft,
                     WallRight,
                     WallTop
    };
    enum LockType {
                    LockNone,
                    LockDigital,
                    LockKey
    };
    Lbr() = delete;
    ~Lbr() = delete;
};

//parent of all other object classes
class LbrObject {
public:
    LbrObject(Lbr::ObjName n) : name(n) {}
    virtual ~LbrObject() = default;
    Lbr::ObjName getName() const { return name; }
    virtual std::string getNameString() const = 0;
private:
    Lbr::ObjName name;
};

//parent abstract class for container objects
class LbrContainer {
public:
    LbrContainer(Lbr::ObjName n, unsigned int c = 3) : name(n), maxCap(c) {}
    virtual ~LbrContainer(); 
    virtual bool addObject(LbrObject *obj);
    virtual bool removeObject(LbrObject *obj);
    virtual LbrObject* findObject(const Action act) const;
    virtual std::string getNameString() const = 0; 
    Lbr::ObjName getName() const { return name; }
    const std::vector<LbrObject*>& getObjects() const { return objects; }
    int getCapacity() const { return maxCap - objects.size(); }
private:
    Lbr::ObjName name;
    std::vector<LbrObject*> objects;
    unsigned int maxCap;
};

//parent abstract class for lock objects
class LbrLock : public LbrObject {
public:
    LbrLock(Lbr::LockType t, bool lckd = true) : LbrObject(Lbr::ObjLock)
                                               , type(t), locked(lckd) {}
    virtual ~LbrLock() = default;
    Lbr::LockType getType() const { return type; }
    bool isLocked() { return locked; }
    void setLocked(bool lckd) { locked = lckd; }
    virtual std::string getNameString() const = 0;
private:
    Lbr::LockType type;
    bool locked;
};

struct Action {
    Action(Lbr::ActType act = Lbr::ActNone,
           Lbr::ObjName obj = Lbr::ObjNone,
           Lbr::ObjType type = Lbr::None,
           int num = -1)
           : aType(act), oName(obj), oType(type), number(num) {}
    Lbr::ActType aType;
    Lbr::ObjName oName;
    Lbr::ObjType oType;
    //number of object in container if we have more one
    //number == -1 - no specified
    int number;
};

template<class T>
std::string LbrObjectsList(const std::vector<T*>& vec)
{
    std::string result;
    if(vec.empty())
        result = "...";
    else {
        int number = 0;
        for(auto o : vec) {
            result += o->getNameString();
            result += "(" + std::to_string(number) + ")";
            result += ", ";
            number++;
        }
        result.pop_back();
        result[result.size()-1] = '.';
    }
    return result;
}

#endif
