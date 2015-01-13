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
#ifndef GZZZT_ACTION_REQUEST_H
#define GZZZT_ACTION_REQUEST_H

#include <bitset>

#include <gzzzt/shared/ActionType.h>
#include <gzzzt/shared/Request.h>

namespace gzzzt {

    class ActionRequest : public Request {
    public:
        explicit ActionRequest(std::bitset<5> keys, uint8_t playerId);
        explicit ActionRequest(std::vector<uint8_t>& bytes);

        std::bitset<5> getKeys() const;
        uint8_t getPlayerId() const;

        std::vector<uint8_t> serialize() const override;

    private:
        std::bitset<5>  m_keys;
    };
}

#endif  // GZZZT_ACTION_REQUEST_H
