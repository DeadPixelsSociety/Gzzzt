/*
 * Gzzzt, a Bomberman clone with robots and lightnings!
 * Copyright (C) 2014 Gzzzt team (see AUTHORS)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GZZZT_VECTOR_H
#define GZZZT_VECTOR_H

#include <gzzzt/shared/Position.h>

namespace gzzzt {

    struct Vector {
        float x;
        float y;
    };

    inline
    Vector operator-(const Position& lhs, const Position& rhs) {
        return { lhs.x - rhs.x, lhs.y - rhs.y };
    }

    inline
    Vector operator+(const Vector& lhs, const Vector& rhs) {
        return { lhs.x + rhs.x, lhs.y + rhs.y };
    }

    inline
    Vector operator-(const Vector& lhs, const Vector& rhs) {
        return { lhs.x - rhs.x, lhs.y - rhs.y };
    }

    inline
    Vector operator/(const Vector& v, float a) {
        return { v.x / a, v.y / a };
    }

    inline
    bool operator==(const Vector& lhs, const Vector& rhs) {
      return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    inline
    Vector operator-(const Vector& v) {
      return { -v.x, -v.y };
    }

    inline
    float lengthSquared(const Vector& v) {
        return v.x * v.x + v.y * v.y;
    }

}

#endif // GZZZT_VECTOR_H