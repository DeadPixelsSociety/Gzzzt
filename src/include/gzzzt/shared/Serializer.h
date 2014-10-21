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
#ifndef GZZZT_SERIALIZER_H
#define GZZZT_SERIALIZER_H

#include <cstdint>
#include <list>
#include <vector>

namespace gzzzt {

    class Serializer {
    public:
        static std::vector<uint8_t>* serializeFloat(std::vector<uint8_t>* bytes, float f);
        static std::vector<uint8_t>* serializeInt(std::vector<uint8_t>* bytes, int i);

        static float deserializeFloat(std::vector<uint8_t>* bytes);
        static int deserializeInt(std::vector<uint8_t>* bytes);
    };
}

#endif	// GZZZT_SERIALIZER_H
