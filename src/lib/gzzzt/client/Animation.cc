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
#include <client/Animation.h>

#include <iostream>

namespace gzzzt {

  void Animation::addFrame(const AnimationFrame& frame) {
    if (m_frames.empty()) {
      m_current_duration_in_frame = frame.duration;
      m_current_frame = 0;
    }

    m_frames.push_back(frame);
  }

  void Animation::update(float dt) {
    if (m_frames.empty()) {
      return;
    }

    m_current_duration_in_frame -= dt;

    while (m_current_duration_in_frame < 0) {
      m_current_frame = (m_current_frame + 1) % m_frames.size();
      m_current_duration_in_frame += m_frames[m_current_frame].duration;
    }
  }

  sf::Texture *Animation::currentTexture() {
    if (m_frames.empty()) {
      std::cerr << "Error! The animation does not have any frame: " << name() << std::endl;
      return nullptr;
    }

    return m_frames[m_current_frame].texture;
  }

  sf::IntRect Animation::currentTextureRect() {
    if (m_frames.empty()) {
      std::cerr << "Error! The animation does not have any frame: " << name() << std::endl;
      return sf::IntRect();
    }

    return m_frames[m_current_frame].bounds;
  }

}
