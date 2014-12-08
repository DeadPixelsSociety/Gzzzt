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
#include <gzzzt/shared/GameStateResponse.h>
#include <gzzzt/shared/Serializer.h>

namespace gzzzt {

    GameStateResponse::GameStateResponse(std::vector<float> playersPositions)
    : Response(ResponseType::GAME_STATE),
    m_playersPositions(playersPositions) {
    }

    GameStateResponse::GameStateResponse(std::vector<uint8_t>& bytes)
    : Response(bytes) {
        int nbPlayers = static_cast<int> (Serializer::deserializeFloat(bytes));
        for (int i = 0; i < nbPlayers; i++) {
            m_playersPositions.push_back(Serializer::deserializeFloat(bytes)); // Player's ID
            m_playersPositions.push_back(Serializer::deserializeFloat(bytes)); // X
            m_playersPositions.push_back(Serializer::deserializeFloat(bytes)); // Y
        }
    }

    std::vector<float> GameStateResponse::getPlayersPositions() const {
        return m_playersPositions;
    }

    std::vector<uint8_t> GameStateResponse::serialize() const {
        std::vector<uint8_t> bytes = Response::serialize();
        for (float f : m_playersPositions) {
            Serializer::serializeFloat(bytes, f);
        }
        return bytes;
    }
}
