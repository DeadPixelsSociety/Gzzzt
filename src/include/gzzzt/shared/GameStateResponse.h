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

#include <gzzzt/shared/Position.h>
#include <gzzzt/shared/Response.h>
#include <gzzzt/shared/Speed.h>

namespace gzzzt {

    class GameStateResponse : public Response {
    public:
        explicit GameStateResponse(Position pos, Speed speed);
        explicit GameStateResponse(std::vector<uint8_t>& bytes);

        Position getPosition() const;
        Speed getSpeed() const;

        std::vector<uint8_t> serialize() const override;

    private:
        Position m_pos;
        Speed m_speed;
    };
}

#endif	// GAME_STATE_RESPONSE_H
