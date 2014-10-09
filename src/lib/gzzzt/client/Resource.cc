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
