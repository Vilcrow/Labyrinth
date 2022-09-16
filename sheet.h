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

#ifndef SHEET_H_SENTRY
#define SHEET_H_SENTRY

#include <string>
#include "labyrinth.h"

class SheetObject : public LabyrinthObject {
    std::string record;
public:
    SheetObject(const std::string& rec = "");
    ~SheetObject() = default;
    const std::string& getRecord() const { return record; }
    void setRecord(const std::string& rec) { record = rec; }
    std::string handleAction(const Action& act) override;
    std::string getName() const override { return "sheet"; }
};

#endif