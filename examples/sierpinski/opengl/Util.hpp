#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <random>

#include "abcgOpenGL.hpp"

class Util {
public:
  glm::vec2 computeNext(glm::vec2 current, glm::vec2 constant);
  float mod2(glm::vec2 z);
  int computeIteractions(glm::vec2 z0, glm::vec2 constant, int max_iterations);
  // void render(glm::ivec2 render_size, glm::vec2 constant);
};

#endif