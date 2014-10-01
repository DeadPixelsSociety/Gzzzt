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
#ifndef GAME_EVENT_H
#define GAME_EVENT_H

#include <cstdint>
#include <functional>


namespace gzzzt {
  class Entity;

  typedef uint64_t EventType;

#define INVALID_EVENT 0

  constexpr EventType Hash(const char *str, std::size_t sz) {
    return sz == 0 ? 0xcbf29ce484222325 : (str[0] ^ Hash(str + 1, sz - 1)) * 0x100000001b3;
  }

  inline EventType Hash(const std::string& str) {
    return Hash(str.c_str(), str.size());
  }


  struct Event {
    static const EventType type = INVALID_EVENT;
  };

  enum class EventStatus {
    KEEP, /**< The handler must be kept */
    DIE,  /**< The handler can be removed */
  };

  typedef std::function<EventStatus(Entity*, EventType, Event*)> EventHandler;

}

constexpr gzzzt::EventType operator"" _type(const char *str, std::size_t sz) {
  return gzzzt::Hash(str, sz);
}

#endif // GAME_EVENT_H
