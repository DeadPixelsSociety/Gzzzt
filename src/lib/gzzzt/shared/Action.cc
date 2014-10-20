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
#include <gzzzt/shared/Action.h>
#include <gzzzt/shared/Serializer.h>

namespace gzzzt {

    Action::Action(ActionType type, Position pos)
    : m_type(type), m_pos(pos) {
    }
    
    Action::Action(unsigned char* bytes) {
        unsigned int index;
        m_type = (ActionType) bytes[0];
        index = 1;
        m_pos.x = Serializer::deserializeFloat(bytes, &index);
        m_pos.y = Serializer::deserializeFloat(bytes, &index);
    }

    ActionType Action::getType() const {
        return m_type;
    }

    Position Action::getPosition() const {
        return m_pos;
    }

    unsigned char* Action::serialize(unsigned char* bytes, unsigned int* size) const {
        if (bytes == nullptr || size == nullptr) {
            return nullptr;
        }
        bytes[0] = (unsigned char) m_type;
        *size = 1;
        Serializer::serializeFloat(bytes, size, m_pos.x);
        Serializer::serializeFloat(bytes, size, m_pos.y);
        return bytes;
    }
}
