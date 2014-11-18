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

#include <gzzzt/client/ClientMap.h>
#include <gzzzt/client/ClientMapVisitor.h>
#include <tmx/TMX.h>
#include <tmx/TileLayer.h>

namespace gzzzt {

    ClientMap::ClientMap(const boost::filesystem::path & path, ResourceManager & resourceManager) {
        m_tmxMap = tmx::parseMapFile(path);
        m_tileWidth = m_tmxMap->getTileWidth();
        m_tileHeight = m_tmxMap->getTileHeight();
        m_width = m_tmxMap->getWidth();
        m_height = m_tmxMap->getHeight();

        m_staticGIDs = new unsigned int[m_width * m_height];
        m_dynamicGIDs = new unsigned int[m_width * m_height];
        
        int mapLength = m_width * m_height;
        
        for(int i = 0; i < mapLength; ++i) {
            m_dynamicGIDs[i] = 0;
            m_staticGIDs[i] = 0;
        }
        
#if _DEBUG_
        m_tileSetTexture = resourceManager.getTexture("../../src/share/gzzzt/maps/simple/tileset.png");
#else
        //TODO
        assert(true);
#endif

        ClientMapVisitor visitor(m_staticGIDs, m_dynamicGIDs);
        m_tmxMap->visitLayers(visitor);

        loadStaticMap();
    }

    ClientMap::~ClientMap() {
        delete m_tmxMap;
        delete[] m_staticGIDs;
        delete[] m_dynamicGIDs;
    }

    void ClientMap::update(float dt) {
        // TODO
    }

    void ClientMap::render(sf::RenderWindow & window) {

        //static blocks
        window.draw(m_vertices, m_tileSetTexture);

        //dynamic blocks
        int k = 0;

        int mapLength = m_width * m_height;

        for (int index = 0; index < mapLength; ++index) {
            int GID = m_dynamicGIDs[index];
           
            if (GID != 0) {
                unsigned int i = k % m_width;
                unsigned int j = k / m_width;

                assert(j < m_height);

                unsigned int x = i * m_tileWidth;
                unsigned int y = j * m_tileHeight;

                drawGID(x, y, GID, window);
            }

            k++;
        }
    }

    void ClientMap::loadStaticMap() {
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(m_width * m_height * 4);

        int k = 0;

        int mapLength = m_width * m_height;

        for (int index = 0; index < mapLength; ++index) {
            int GID = m_staticGIDs[index];

            if (GID == 0) {
                continue;
            }

            unsigned int i = k % m_width;
            unsigned int j = k / m_width;

            assert(j < m_height);

            unsigned int x = i * m_tileWidth;
            unsigned int y = j * m_tileHeight;

            sf::Vertex* quad = &m_vertices[(i + j * m_width) * 4];

            quad[0].position = sf::Vector2f(x, y);
            quad[1].position = sf::Vector2f(x + m_tileWidth, y);
            quad[2].position = sf::Vector2f(x + m_tileWidth, y + m_tileHeight);
            quad[3].position = sf::Vector2f(x, y + m_tileHeight);

            tmx::TileSet *tileset = m_tmxMap->getTileSetFromGID(GID);
            GID = GID - tileset->getFirstGID();

            if (tileset->hasImage()) {
                const tmx::Image *image = tileset->getImage();

                tmx::Size size = image->getSize();
                tmx::Rect rect = tileset->getCoords(GID, size);

                quad[0].texCoords = sf::Vector2f(rect.x, rect.y);
                quad[1].texCoords = sf::Vector2f(rect.x + rect.width, rect.y);
                quad[2].texCoords = sf::Vector2f(rect.x + rect.width, rect.y + rect.height);
                quad[3].texCoords = sf::Vector2f(rect.x, rect.y + rect.height);
            }

            k++;
        }
    }

    void ClientMap::drawGID(unsigned int x, unsigned int y, unsigned int GID, sf::RenderWindow & window) {

        tmx::TileSet *tileset = m_tmxMap->getTileSetFromGID(GID);
        
        GID = GID - tileset->getFirstGID();
        
        if (tileset->hasImage()) {
            const tmx::Image *image = tileset->getImage();

            tmx::Size size = image->getSize();
            tmx::Rect rect = tileset->getCoords(GID, size);

            sf::IntRect subRect;
            subRect.left = rect.x;
            subRect.height = rect.height;
            subRect.top = rect.y;
            subRect.width = rect.width;

            sf::Sprite sprite(*m_tileSetTexture);
            sprite.setTextureRect(subRect);
            sprite.setPosition(x, y);
            window.draw(sprite);
        }
    }
}
