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
#ifndef GZZZT_SERVER_MAP_H
#define GZZZT_SERVER_MAP_H

#include <vector>
#include <tmx/Map.h>
#include <boost/filesystem.hpp>

#include <gzzzt/server/ServerEntity.h>
#include <gzzzt/shared/Block.h>

namespace gzzzt {

    class ServerMap : public ServerEntity {
    public:

        ServerMap(const boost::filesystem::path & path);
        virtual ~ServerMap();

        virtual void update(float dt) override;
    private:

    public:


    private:
        tmx::Map* m_tmxMap;
        
        unsigned int m_mapLength;
        unsigned int m_tileWidth;
        unsigned int m_tileHeight;
        unsigned int m_width;
        unsigned int m_height;
    };

}


#endif // GZZZT_SERVER_MAP_H
