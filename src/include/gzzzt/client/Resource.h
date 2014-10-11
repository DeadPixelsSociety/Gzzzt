/*
 * Gzzzt, a Bomberman clone with robots and lightnings!
 * Copyright (C) 2014 Gzzzt team (see AUTHORS)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GZZZT_RESOURCE_H
#define GZZZT_RESOURCE_H

#include <string>
#include <map>
#include <memory>
#include <vector>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace gzzzt {

  template<typename T>
  class ResourceCache {
  public:
    T *findResource(const std::string& key);
    T *loadResource(const std::string& key, const std::string& path);
  private:
    std::map<std::string, std::unique_ptr<T>> m_cache;
  };

  extern template class ResourceCache<sf::Font>;
  extern template class ResourceCache<sf::SoundBuffer>;
  extern template class ResourceCache<sf::Texture>;

  class ResourceManager {
  public:
    void addSearchDir(std::string path);

    sf::Font *getFont(const std::string& path);
    sf::SoundBuffer *getSoundBuffer(const std::string& path);
    sf::Texture *getTexture(const std::string& path);

  private:
    std::vector<std::string> m_searchdirs;

    ResourceCache<sf::Font> m_fonts;
    ResourceCache<sf::SoundBuffer> m_sounds;
    ResourceCache<sf::Texture> m_textures;

  private:
    template<typename T>
    T *getResource(const std::string& path, ResourceCache<T>& cache);
  };


}

#endif // GZZZT_RESOURCE_H
