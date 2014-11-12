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
#include <gzzzt/shared/Serializer.h>
#include <gzzzt/shared/StartGameResponse.h>

namespace gzzzt {

    StartGameResponse::StartGameResponse(const std::vector<std::string>& playersName)
    : Response(ResponseType::START_GAME),
    m_playersName(playersName) {
    }

    StartGameResponse::StartGameResponse(std::vector<uint8_t>* bytes) : Response(bytes) {
        int size = gzzzt::Serializer::deserializeInt(bytes);
        for (int i = 0; i < size; i++) {
            int length = gzzzt::Serializer::deserializeInt(bytes);
            m_playersName.push_back(Serializer::deserializeString(bytes, length));
        }
    }

    std::vector<std::string> StartGameResponse::getPlayersName() const {
        return m_playersName;
    }

    std::vector<uint8_t>* StartGameResponse::serialize(std::vector<uint8_t>* bytes) const {
        if (Response::serialize(bytes) == nullptr) {
            return nullptr;
        }
        gzzzt::Serializer::serializeInt(bytes, m_playersName.size());
        for (auto name : m_playersName) {
            gzzzt::Serializer::serializeInt(bytes, name.length());
            gzzzt::Serializer::serializeString(bytes, name);
        }
        return bytes;
    }
}
