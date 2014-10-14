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
#include <gzzzt/client/World.h>

#include <cassert>
#include <algorithm>
#include <memory>

namespace gzzzt {

  namespace {

    template<typename T>
    class null_delete {
    public:
      void operator()(T*) const {
        // nothing to do
      }
    };

  }

  void World::update(float dt) {
    std::sort(m_entities.begin(), m_entities.end(), [](const ClientEntityPtr& e1, const ClientEntityPtr& e2) {
      return e1->priority() < e2->priority();
    });

    for (auto& entity : m_entities) {
      entity->update(dt);
    }
  }

  void World::render(sf::RenderWindow& window) {
    for (auto& entity : m_entities) {
      entity->render(window);
    }
  }

  void World::addEntity(ClientEntity *e, Memory from) {
    switch (from) {
      case Memory::FROM_HEAP:
        m_entities.emplace_back(e, std::default_delete<ClientEntity>());
        break;
      case Memory::FROM_STACK:
        m_entities.emplace_back(e, null_delete<ClientEntity>());
        break;
    }
  }

  void World::removeEntity(ClientEntity *e) {
    std::remove_if(m_entities.begin(), m_entities.end(), [=](const ClientEntityPtr& ptr) {
      return e == ptr.get();
    });
  }

  void World::registerHandler(EventType type, EventHandler handler) {
    assert(handler);
    auto it = m_handlers.find(type);

    if (it == m_handlers.end()) {
      bool inserted;
      std::tie(it, inserted) = m_handlers.insert(std::make_pair(type, std::vector<EventHandler>()));
      assert(inserted);
    }

    it->second.push_back(handler);
  }

  void World::triggerEvent(ClientEntity *origin, EventType type, Event *event) {
    auto it = m_handlers.find(type);

    if (it == m_handlers.end()) {
      return;
    }

    std::vector<EventHandler> kept;

    for (auto handler : it->second) {
      if (handler(origin, type, event) == EventStatus::KEEP) {
        kept.push_back(handler);
      }
    }

    std::swap(it->second, kept);
  }

}
