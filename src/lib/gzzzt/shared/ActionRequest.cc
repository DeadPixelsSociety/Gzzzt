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
#include <gzzzt/shared/ActionRequest.h>
#include <gzzzt/shared/Serializer.h>

namespace gzzzt {

    ActionRequest::ActionRequest(ActionType type, uint8_t playerId)
    : Request(RequestType::ACTION, playerId),
    m_type(type) {
    }

    ActionRequest::ActionRequest(std::vector<uint8_t>& bytes) : Request(bytes) {
        m_type = static_cast<ActionType> (bytes[0]);
        bytes.erase(bytes.begin());
    }

    ActionType ActionRequest::getType() const {
        return m_type;
    }

    uint8_t ActionRequest::getPlayerId() const {
        return m_playerId;
    }

    std::vector<uint8_t> ActionRequest::serialize() const {
        std::vector<uint8_t> bytes = Request::serialize();
        bytes.push_back(static_cast<uint8_t> (m_type));
        return bytes;
    }
}
