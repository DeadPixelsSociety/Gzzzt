/*
 * Copyright (c) 2014, Julien Bernard
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef GAME_RESOURCE_H
#define GAME_RESOURCE_H

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

#endif // GAME_RESOURCE_H
