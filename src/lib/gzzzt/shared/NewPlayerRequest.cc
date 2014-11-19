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
#include <gzzzt/shared/NewPlayerRequest.h>
#include <gzzzt/shared/Serializer.h>

namespace gzzzt {

    NewPlayerRequest::NewPlayerRequest(std::string playerName)
    : Request(RequestType::NEW_PLAYER),
    m_playerName(playerName) {
    }

    NewPlayerRequest::NewPlayerRequest(std::vector<uint8_t>& bytes)
    : Request(bytes) {
        m_playerName = Serializer::deserializeString(bytes);
    }
    
    std::string NewPlayerRequest::getPlayerName() const {
        return m_playerName;
    }

    std::vector<uint8_t> NewPlayerRequest::serialize() const {
        std::vector<uint8_t> bytes = Request::serialize();
        Serializer::serializeString(bytes, m_playerName);
        return bytes;
    }
}
