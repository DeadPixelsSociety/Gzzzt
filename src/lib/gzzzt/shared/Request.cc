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
#include <gzzzt/shared/Request.h>
#include <gzzzt/shared/Serializer.h>

namespace gzzzt {

    Request::Request(RequestType type, uint8_t playerId)
    : m_reqType(type),
    m_playerId(playerId) {
    }

    Request::Request(std::vector<uint8_t>& bytes) {
        m_reqType = static_cast<RequestType> (gzzzt::Serializer::deserializeInt8(bytes));
        m_playerId = gzzzt::Serializer::deserializeInt8(bytes);
    }

    Request::~Request() {
    }

    RequestType Request::getReqType() const {
        return m_reqType;
    }

    uint8_t Request::getPlayerId() const {
        return m_playerId;
    }

    std::vector<uint8_t> Request::serialize() const {
        std::vector<uint8_t> bytes;
        Serializer::serializeInt8(bytes, static_cast<uint8_t> (m_reqType));
        Serializer::serializeInt8(bytes, m_playerId);
        return bytes;
    }

    RequestType Request::getType(std::vector<uint8_t> bytes) {
        return static_cast<RequestType> (bytes[0]);
    }
}
