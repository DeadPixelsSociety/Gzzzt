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
#include <gzzzt/shared/Response.h>
#include <gzzzt/shared/Serializer.h>

namespace gzzzt {

    Response::Response(Position pos, Speed speed)
    : m_pos(pos), m_speed(speed) {
    }

    Response::Response(std::vector<uint8_t>* bytes) {
        m_pos.x = Serializer::deserializeFloat(bytes);
        m_pos.y = Serializer::deserializeFloat(bytes);
        m_speed.dx = Serializer::deserializeFloat(bytes);
        m_speed.dy = Serializer::deserializeFloat(bytes);
    }

    Position Response::getPosition() const {
        return m_pos;
    }

    Speed Response::getSpeed() const {
        return m_speed;
    }

    std::vector<uint8_t>* Response::serialize(std::vector<uint8_t>* bytes) const {
        Serializer::serializeFloat(bytes, m_pos.x);
        Serializer::serializeFloat(bytes, m_pos.y);
        Serializer::serializeFloat(bytes, m_speed.dx);
        Serializer::serializeFloat(bytes, m_speed.dy);
        return bytes;
    }
}
