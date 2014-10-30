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
#ifndef GZZZT_REQUEST_H
#define GZZZT_REQUEST_H

#include <gzzzt/shared/RequestType.h>
#include <gzzzt/shared/Serializable.h>

namespace gzzzt {
    
    class Request : public gzzzt::Serializable {
    public:
        explicit Request(std::vector<uint8_t>* bytes, bool erase = true);
        virtual ~Request();
        
    protected:
        explicit Request(RequestType type);
        
    public:
        RequestType getReqType() const;
        
        std::vector<uint8_t>* serialize(std::vector<uint8_t>* bytes) const override;
        
    private:
        RequestType m_reqType;
    };
}

#endif	// GZZZT_REQUEST_H
