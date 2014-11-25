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
#include <gzzzt/shared/Log.h>
#include <gzzzt/shared/Serializer.h>
#include <gzzzt/shared/StartGameResponse.h>

namespace gzzzt {

    StartGameResponse::StartGameResponse(const std::map<uint8_t, std::string>& players, unsigned short serverPort)
    : Response(ResponseType::START_GAME),
    m_players(players),
    m_serverPortUDP(serverPort) {
    }

    StartGameResponse::StartGameResponse(std::vector<uint8_t>& bytes) : Response(bytes) {
        int size = gzzzt::Serializer::deserializeInt(bytes);
        for (int i = 0; i < size; i++) {
            int id = Serializer::deserializeInt8(bytes);
            std::string name = Serializer::deserializeString(bytes);
            m_players.insert(std::pair<uint8_t, std::string>(id, name));
        }
        m_serverPortUDP = Serializer::deserializeUShort(bytes);
    }

    std::map<uint8_t, std::string> StartGameResponse::getPlayers() const {
        return m_players;
    }

    unsigned short StartGameResponse::getServerPortUDP() const {
        return m_serverPortUDP;
    }

    std::vector<uint8_t> StartGameResponse::serialize() const {
        std::vector<uint8_t> bytes = Response::serialize();
        gzzzt::Serializer::serializeInt(bytes, static_cast<int> (m_players.size()));
        for (auto player : m_players) {
            gzzzt::Serializer::serializeInt8(bytes, player.first);
            gzzzt::Serializer::serializeString(bytes, player.second);
        }
        gzzzt::Serializer::serializeUShort(bytes, m_serverPortUDP);
        return bytes;
    }
}
