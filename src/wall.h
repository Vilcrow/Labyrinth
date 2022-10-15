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

#ifndef WALL_H_SENTRY
#define WALL_H_SENTRY

#include "labyrinth.h"
#include <vector>

class Wall {
public:
    Wall() = default;
    virtual ~Wall();
    bool addContainer(LbrContainer *container);
    LbrContainer* findContainer(const Action act);
    const std::vector<LbrContainer*>& getContainers() const { return containers; }
    static Lbr::WallType getWallType(const Lbr::ObjName name);
    Lbr::ObjName getName() const { return Lbr::ObjWall; }
    std::string getNameString() const { return "wall"; }
private:
    enum { maxCapacity = 4 };
    std::vector<LbrContainer*> containers;
};

#endif
