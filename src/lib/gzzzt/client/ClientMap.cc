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

    ClientMap::ClientMap(const boost::filesystem::path & path) {
        m_tmxMap = tmx::parseMapFile(path);
        m_tileWidth = m_tmxMap->getTileWidth();
        m_tileHeight = m_tmxMap->getTileHeight();
        m_width = m_tmxMap->getWidth();
        m_height = m_tmxMap->getHeight();

        m_resourceManager.addSearchDir("../");
        m_tileSetTexture = m_resourceManager.getTexture("src/share/gzzzt/maps/simple/tileset.png");

        ClientMapVisitor visitor(&m_GID);
        m_tmxMap->visitLayers(visitor);
    }

    ClientMap::~ClientMap() {
        delete m_tmxMap;
    }

    void ClientMap::update(float dt) {
        // TODO

    }

    void ClientMap::render(sf::RenderWindow& window) {
        unsigned int k = 0;

        for (int GID : m_GID) {
            unsigned int i = k % m_width;
            unsigned int j = k / m_width;

            assert(j < m_height);

            unsigned int x = i * m_tileWidth;
            unsigned int y = j * m_tileHeight;

            drawGID(x, y, GID, window);
            k++;
        }
    }

    void ClientMap::drawGID(unsigned int x, unsigned int y, unsigned int GID, sf::RenderWindow& window) {
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
