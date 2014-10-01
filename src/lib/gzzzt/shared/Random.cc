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
#include <shared/Random.h>

#include <ctime>

namespace gzzzt {

  Random::Random()
  : m_engine(std::time(nullptr))
  {

  }

  Random::Random(unsigned seed)
  : m_engine(seed)
  {

  }


  int Random::computeUniformInteger(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_engine);
  }

  float Random::computeUniformFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_engine);
  }

  float Random::computeNormalFloat(float mean, float stddev) {
    std::normal_distribution<float> dist(mean, stddev);
    return dist(m_engine);
  }

}
