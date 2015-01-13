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

    ServerMapVisitor::ServerMapVisitor(ServerMap* map, Physics* p) {
        m_map = map;
        m_physics = p;
        m_tileIndex = 0;
        m_tileWidth = map->getTmxMap()->getTileWidth();
        m_tileHeight = map->getTmxMap()->getTileHeight();
        m_width = map->getTmxMap()->getWidth();
        m_height = map->getTmxMap()->getHeight();
        m_mapLength = m_width * m_height;
    }

    void ServerMapVisitor::visitTileLayer(tmx::TileLayer& layer) {

        if (strcmp(layer.getName().c_str(), "Background") == 0) {

            /*for (auto obj : layer) {

                if (obj.getGID() != 0) {
                    std::cout << "bg" << std::endl;
                    Body* body = new Body();
                    body->type = Body::Type::STATIC;
                    body->shape.kind = Shape::RECTANGLE;
                    body->shape.rectangle.height = m_tileHeight;
                    body->shape.rectangle.width = m_tileWidth;
                    body->pos.x = m_tileIndex % m_width;
                    body->pos.y = m_tileIndex / m_width;
                    body->velocity = {0., 0.};
                    body->layers = Body::ALL_LAYERS;
                    m_physics->addBody(body);
                }
                
                m_tileIndex++;
                if (m_tileIndex == m_mapLength) {
                    m_tileIndex = 0;
                }
            }*/
        } else if (strcmp(layer.getName().c_str(), "Adamantium") == 0) {

            for (auto obj : layer) {

                if (obj.getGID() != 0) {

                    Body* body = new Body();
                    body->type = Body::Type::STATIC;
                    body->shape.kind = Shape::RECTANGLE;
                    body->shape.rectangle.height = m_tileHeight;
                    body->shape.rectangle.width = m_tileWidth;
                    body->pos.x = (m_tileIndex % m_width) * m_tileWidth;
                    body->pos.y = (m_tileIndex / m_width) * m_tileHeight;
                    body->velocity = {0., 0.};
                    body->layers = Body::ALL_LAYERS;
                    m_physics->addBody(body);
                }

                m_tileIndex++;
                if (m_tileIndex == m_mapLength) {
                    m_tileIndex = 0;
                }
            }
        } else if (strcmp(layer.getName().c_str(), "Aluminium") == 0) {
            for (auto obj : layer) {

                if (obj.getGID() != 0) {
                    Body* body = new Body();
                    body->type = Body::Type::STATIC;
                    body->shape.kind = Shape::CIRCLE;
                    body->shape.circle.radius = m_tileWidth / 2;
                    body->pos.x = (m_tileIndex % m_width) * m_tileWidth;
                    body->pos.y = (m_tileIndex / m_width) * m_tileHeight;
                    body->velocity = {0., 0.};
                    body->layers = Body::ALL_LAYERS;
                    m_physics->addBody(body);
                }
                m_tileIndex++;
                if (m_tileIndex == m_mapLength) {
                    m_tileIndex = 0;
                }
            }
        }
    }

    void ServerMapVisitor::visitObjectLayer(tmx::ObjectLayer & layer) {
    }

    void ServerMapVisitor::visitImageLayer(tmx::ImageLayer & layer) {
    }
}
