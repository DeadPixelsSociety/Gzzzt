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

#include <cstdio>
#include <cstring>
#include <gzzzt/client/ClientMapVisitor.h>
#include <tmx/ObjectLayer.h>
#include <tmx/TileLayer.h>
#include <tmx/Tile.h>

namespace gzzzt {

    ClientMapVisitor::ClientMapVisitor(unsigned int* staticGIDs, unsigned int* dynamicGIDs) {
        m_staticGIDs = staticGIDs;
        m_dynamicGIDs = dynamicGIDs;
    }

    void ClientMapVisitor::visitTileLayer(tmx::TileLayer& layer) {
        
        if (strcmp(layer.getName().c_str(), "Background") == 0) {
            int index = 0;
            for (auto obj : layer) {

                if (obj.getGID() != 0) {
                    m_staticGIDs[index] = obj.getGID();
                }
                
                index++;
            }
        } else if (strcmp(layer.getName().c_str(), "Adamantium") == 0) {
            int index = 0;

            for (auto obj : layer) {
                if (obj.getGID() != 0) {
                    m_staticGIDs[index] = obj.getGID();
                }

                index++;
            }
        } else if (strcmp(layer.getName().c_str(), "Aluminium") == 0) {
            int index = 0;

            for (auto obj : layer) {
                if (obj.getGID() != 0) {
                    m_dynamicGIDs[index] = obj.getGID();
                }

                index++;
            }
        }
    }

    void ClientMapVisitor::visitObjectLayer(tmx::ObjectLayer& layer) {
    }

    void ClientMapVisitor::visitImageLayer(tmx::ImageLayer& layer) {
    }
}
