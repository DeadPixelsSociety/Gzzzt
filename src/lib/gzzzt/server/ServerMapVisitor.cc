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
#include <gzzzt/server/ServerMapVisitor.h>
#include <tmx/ObjectLayer.h>
#include <tmx/TileLayer.h>
#include <tmx/Tile.h>

namespace gzzzt {

    ServerMapVisitor::ServerMapVisitor(ServerMap* map) {
        m_map = map;
    }

    void ServerMapVisitor::visitTileLayer(tmx::TileLayer& layer) {

        if (strcmp(layer.getName().c_str(), "Background") == 0) {

        } else if (strcmp(layer.getName().c_str(), "Adamantium") == 0) {

        } else if (strcmp(layer.getName().c_str(), "Aluminium") == 0) {

        }
    }

    void ServerMapVisitor::visitObjectLayer(tmx::ObjectLayer& layer) {
    }

    void ServerMapVisitor::visitImageLayer(tmx::ImageLayer& layer) {
    }
}
