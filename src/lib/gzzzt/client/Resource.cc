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
#include <gzzzt/client/Resource.h>

#include <iostream>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace gzzzt {

    template<typename T>
    T *ResourceCache<T>::findResource(const std::string& key) {
        auto it = m_cache.find(key);

        if (it != m_cache.end()) {
            return it->second.get();
        }

        return nullptr;
    }

    template<typename T>
    T *ResourceCache<T>::loadResource(const std::string& key, const std::string& path) {
        std::unique_ptr<T> obj(new T);

        bool loaded = obj->loadFromFile(path);
        assert(loaded);

        auto inserted = m_cache.emplace(key, std::move(obj));
        assert(inserted.second);

        return inserted.first->second.get();
    }

    template class ResourceCache<sf::Font>;
    template class ResourceCache<sf::SoundBuffer>;
    template class ResourceCache<sf::Texture>;


    void ResourceManager::addSearchDir(std::string path) {
        m_searchdirs.emplace_back(std::move(path));
    }

    sf::Font *ResourceManager::getFont(const std::string& path) {
        return getResource(path, m_fonts);
    }

    sf::SoundBuffer *ResourceManager::getSoundBuffer(const std::string& path) {
        return getResource(path, m_sounds);
    }

    sf::Texture *ResourceManager::getTexture(const std::string& path) {
        return getResource(path, m_textures);
    }

    template<typename T>
    T *ResourceManager::getResource(const std::string& path, ResourceCache<T>& cache) {
        auto res = cache.findResource(path);

        if (res != nullptr) {
            return res;
        }

        fs::path file(path);

        for (fs::path base : m_searchdirs) {
            fs::path absolute_path = base / file;

            if (fs::is_regular_file(absolute_path)) {
                std::clog << "Found a resource file: " << absolute_path << std::endl;
                return cache.loadResource(path, absolute_path.string());
            }
        }

        std::cerr << "Error! Could not find the following file: " << path << std::endl;
        return nullptr;
    }

}
