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
#ifndef GZZZT_IDENTIFY_REQUEST_H
#define GZZZT_IDENTIFY_REQUEST_H

#include <gzzzt/shared/Request.h>

namespace gzzzt {

    class IdentifyRequest : public Request {
    public:
        explicit IdentifyRequest(uint8_t id);
        explicit IdentifyRequest(std::vector<uint8_t>& bytes);

        uint8_t getID() const;

        std::vector<uint8_t> serialize() const override;

    private:
        uint8_t m_id;
    };
}

#endif  // GZZZT_IDENTIFY_REQUEST_H
