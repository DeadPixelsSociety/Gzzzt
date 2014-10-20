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
#include <cstring>

#include <gzzzt/shared/Serializer.h>

namespace gzzzt {

    unsigned char* Serializer::serializeFloat(unsigned char* bytes, unsigned int* size, float f) {
        unsigned char const* floatBytes = reinterpret_cast<unsigned char const*>(&f);
        for (std::size_t i = 0; i < sizeof(float); i++) {
            bytes[*size + i] = floatBytes[i];
        }
        *size += sizeof(float);
        return bytes;
    }

    float Serializer::deserializeFloat(unsigned char* bytes, unsigned int *index) {
        float f;
        std::memcpy(&f, bytes + *index, sizeof(float));
        *index += sizeof(float);
        return f;
    }
}
