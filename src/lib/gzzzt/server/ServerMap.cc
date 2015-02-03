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

#include <gzzzt/server/ServerMap.h>
#include <gzzzt/server/ServerMapVisitor.h>
#include <tmx/TMX.h>
#include <tmx/TileLayer.h>

namespace gzzzt {

    ServerMap::ServerMap(const boost::filesystem::path & path, gzzzt::ResourceManager& resourceManager) {
        m_tmxMap = resourceManager.getMap(path.string());
        m_tileHeight = m_tmxMap->getTileHeight();
        m_tileWidth = m_tmxMap->getTileWidth();
    }

    ServerMap::~ServerMap() {
        delete m_tmxMap;
    }

    void ServerMap::update(float dt) {
        // TODO
    }

    tmx::Map* ServerMap::getTmxMap() const {
        return m_tmxMap;
    }

    unsigned int ServerMap::getTileHeight() const {
        return m_tileHeight;
    }

    unsigned int ServerMap::getTileWidth() const {
        return m_tileWidth;
    }

    void ServerMap::load(Physics* p) {
        ServerMapVisitor visitor(this, p);
        m_tmxMap->visitLayers(visitor);
    }
}
