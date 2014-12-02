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
#include <string>
#include <vector>

namespace gzzzt {

    class Serializer {
    public:
        static void serializeFloat(std::vector<uint8_t>& bytes, float f);
        static void serializeInt(std::vector<uint8_t>& bytes, int i);
        static void serializeInt8(std::vector<uint8_t>& bytes, uint8_t i);
        static void serializeUShort(std::vector<uint8_t>& bytes, unsigned short s);
        static void serializeString(std::vector<uint8_t>& bytes, std::string s);

        static float deserializeFloat(std::vector<uint8_t>& bytes);
        static int deserializeInt(std::vector<uint8_t>& bytes);
        static uint8_t deserializeInt8(std::vector<uint8_t>& bytes);
        static unsigned short deserializeUShort(std::vector<uint8_t>& bytes);
        static std::string deserializeString(std::vector<uint8_t>& bytes);
    };
}

#endif	// GZZZT_SERIALIZER_H
