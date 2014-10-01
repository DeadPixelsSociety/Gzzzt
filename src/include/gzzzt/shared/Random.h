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
#ifndef GAME_RANDOM_H
#define GAME_RANDOM_H

#include <random>
#include <functional>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

namespace gzzzt {

  class Random {
  public:
    Random();
    Random(unsigned seed);

    int computeUniformInteger(int min, int max);

    float computeUniformFloat(float min, float max);

    float computeNormalFloat(float mean, float stddev);

  private:
    std::mt19937 m_engine;
  };

}

#endif // GAME_RANDOM_H
