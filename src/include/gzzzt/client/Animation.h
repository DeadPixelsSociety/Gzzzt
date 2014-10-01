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
#ifndef GAME_ANIMATION_H
#define GAME_ANIMATION_H

#include <vector>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <client/Entity.h>

namespace gzzzt {

  struct AnimationFrame {
    sf::Texture *texture;
    sf::IntRect bounds;
    float duration;
  };

  class Animation {
  public:
    Animation(std::string name)
    : m_name(std::move(name)) {
    }

    const std::string& name() {
      return m_name;
    }

    void addFrame(const AnimationFrame& frame);

    void update(float dt);

    sf::Texture *currentTexture();
    sf::IntRect currentTextureRect();

  private:
    std::string m_name;
    std::size_t m_current_frame = 0;
    float m_current_duration_in_frame = 0.0f;
    std::vector<AnimationFrame> m_frames;
  };

}

#endif // GAME_ANIMATION_H
