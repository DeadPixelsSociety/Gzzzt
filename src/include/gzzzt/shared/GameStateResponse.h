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
#ifndef GAME_STATE_RESPONSE_H
#define GAME_STATE_RESPONSE_H

#include <gzzzt/shared/Response.h>

namespace gzzzt {

    class GameStateResponse : public Response {
    public:
        explicit GameStateResponse(std::vector<float>& playersPositions,
                std::vector<float>& bombsPositions);
        explicit GameStateResponse(std::vector<uint8_t>& bytes);

        std::vector<float> getPlayersPositions() const;
        std::vector<float> getBombsPositions() const;

        std::vector<uint8_t> serialize() const override;

    private:
        std::vector<float> m_playersPositions;
        std::vector<float> m_bombsPositions;
    };
}

#endif	// GAME_STATE_RESPONSE_H
