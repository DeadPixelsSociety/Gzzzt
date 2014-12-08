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
#ifndef GZZZT_SERVER_MAP_VISITOR_H
#define GZZZT_SERVER_MAP_VISITOR_H

#include <vector>
#include <tmx/LayerVisitor.h>

#include <gzzzt/server/Physics.h>
#include <gzzzt/server/ServerMap.h>

namespace gzzzt {

    class ServerMapVisitor : public tmx::LayerVisitor {
    public:
        
        ServerMapVisitor(ServerMap* map, Physics* p);
        
        virtual void visitTileLayer(tmx::TileLayer& layer) override;
        virtual void visitObjectLayer(tmx::ObjectLayer& layer) override;
        virtual void visitImageLayer(tmx::ImageLayer& layer) override;
        
    private:
        ServerMap* m_map;
        Physics* m_physics;
        unsigned int m_tileIndex;
        unsigned int m_tileWidth;
        unsigned int m_tileHeight;
        unsigned int m_width;
        unsigned int m_height;   
        unsigned int m_mapLength;
    };

}

#endif // GZZZT_SERVER_MAP_VISITOR_H
