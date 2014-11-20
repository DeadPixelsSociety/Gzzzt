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
#include <gzzzt/shared/Response.h>
#include <gzzzt/shared/Serializer.h>

namespace gzzzt {
 
    Response::Response(ResponseType type) : m_respType(type) {
    }

    Response::Response(std::vector<uint8_t>& bytes) {
        m_respType = static_cast<ResponseType>(bytes[0]);
        bytes.erase(bytes.begin());
    }
    
    Response::~Response() {
    }

    ResponseType Response::getRespType() const {
        return m_respType;
    }

    std::vector<uint8_t> Response::serialize() const {
        std::vector<uint8_t> bytes;
        bytes.push_back(static_cast<uint8_t>(m_respType));
        return bytes;
    }

    ResponseType Response::getType(std::vector<uint8_t> bytes) {
        return static_cast<ResponseType>(bytes[0]);
    }
}
