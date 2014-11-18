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
#include <gzzzt/shared/ErrorResponse.h>
#include <gzzzt/shared/Serializer.h>

namespace gzzzt {

    ErrorResponse::ErrorResponse(std::string reason)
    : Response(ResponseType::ERROR),
    m_reason(reason) {
    }

    ErrorResponse::ErrorResponse(std::vector<uint8_t>& bytes)
    : Response(bytes) {
        m_reason = Serializer::deserializeString(bytes);
    }

    std::string ErrorResponse::getReason() const {
        return m_reason;
    }

    std::vector<uint8_t> ErrorResponse::serialize() const {
        std::vector<uint8_t> bytes, respBytes;
        respBytes = Response::serialize();
        bytes.insert(bytes.end(), respBytes.begin(), respBytes.end());
        Serializer::serializeString(bytes, m_reason);
        return bytes;
    }
}
