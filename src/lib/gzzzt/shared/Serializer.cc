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

    void Serializer::serializeFloat(std::vector<uint8_t>& bytes, float f) {
        const uint8_t* floatBytes = reinterpret_cast<const uint8_t*> (&f);
        for (std::size_t i = 0; i < sizeof (float); i++) {
            bytes.push_back(floatBytes[i]);
        }
    }

    void Serializer::serializeInt(std::vector<uint8_t>& bytes, int integer) {
        int shift = ((sizeof (int) - 1) * 8); // = 24 if sizeof(int) = 4 (32 bits)
        int mask = 0xFF << shift; // = 0xFF000000 if sizeof(int) = 4
        for (std::size_t i = 0; i < sizeof (int); i++) {
            bytes.push_back(static_cast<uint8_t> ((integer & mask) >> shift));
            shift -= 8;
            mask >>= 8;
        }
    }

    void Serializer::serializeInt8(std::vector<uint8_t>& bytes, uint8_t i) {
        bytes.push_back(i);
    }

    void Serializer::serializeUShort(std::vector<uint8_t>& bytes, unsigned short s) {
        int shift = ((sizeof (short) - 1) * 8); // = 8 if sizeof(short) = 2 (16 bits)
        int mask = 0xFF << shift; // = 0xFF00 if sizeof(short) = 2
        for (std::size_t i = 0; i < sizeof (short); i++) {
            bytes.push_back(static_cast<uint8_t> ((s & mask) >> shift));
            shift -= 8;
            mask >>= 8;
        }
    }

    void Serializer::serializeString(std::vector<uint8_t>& bytes, std::string s) {
        serializeInt(bytes, static_cast<int> (s.length()));
        for (std::size_t i = 0; i < s.length(); i++) {
            bytes.push_back(static_cast<uint8_t> (s.at(i)));
        }
    }

    float Serializer::deserializeFloat(std::vector<uint8_t>& bytes) {
        float f = 0.f;
        std::memcpy(&f, &bytes[0], sizeof (float));
        auto it = bytes.begin();
        bytes.erase(it, it + sizeof (float)); // Remove the first sizeof(float) elements
        return f;
    }

    int Serializer::deserializeInt(std::vector<uint8_t>& bytes) {
        int shift = ((sizeof (int) - 1) * 8); // = 24 if sizeof(int) = 4 (32 bits)
        int integer = 0;
        for (std::size_t i = 0; i < sizeof (int); i++) {
            integer |= bytes[0] << shift;
            bytes.erase(bytes.begin());
            shift -= 8;
        }
        return integer;
    }

    unsigned short Serializer::deserializeUShort(std::vector<uint8_t>& bytes) {
        int shift = ((sizeof (short) - 1) * 8); // = 8 if sizeof(short) = 2 (16 bits)
        unsigned short ushort = 0;
        for (std::size_t i = 0; i < sizeof (short); i++) {
            ushort |= bytes[0] << shift;
            bytes.erase(bytes.begin());
            shift -= 8;
        }
        return ushort;
    }

    uint8_t Serializer::deserializeInt8(std::vector<uint8_t>& bytes) {
        uint8_t integer = bytes.front();
        bytes.erase(bytes.begin(), bytes.begin() + 1);
        return integer;
    }

    std::string Serializer::deserializeString(std::vector<uint8_t>& bytes) {
        int length = deserializeInt(bytes);
        std::string str(bytes.begin(), bytes.begin() + length);
        bytes.erase(bytes.begin(), bytes.begin() + length);
        return str;
    }
}
