#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <random>

#include "abcgOpenGL.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onCreate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;

private:
  glm::ivec2 m_viewportSize{};
  GLuint m_VAO{};
  GLuint m_VBOVertices{};
  GLuint m_program{};
  GLfloat constant_real_part{-0.745f};
  GLfloat constant_imag_part{-0.097f};
  std::array<float, 4> m_clearColor{0.906f, 0.910f, 0.918f, 1.0f};
  GLfloat max_iter_r{0.906f};
  GLfloat max_iter_g{0.910f};
  GLfloat max_iter_b{0.918f};


  float real_part{-0.745f};
  float imag_part{-0.097f};

  bool animate_real{false};
  bool animate_imag{false};

  float real_acumulator{0.5};
  float imag_acumulator{-2.0};

  std::default_random_engine m_randomEngine;
  std::array<glm::vec2, 4> const vetex{{{-1, -1}, {-1, 1}, {1, 1}, {1, -1}}};

  void setupModel();


  abcg::Timer m_timer;
  int m_delay{200};

  glm::vec2 computeNext(glm::vec2 current, glm::vec2 constant);
  float mod2(glm::vec2 z);
  int computeIteractions(glm::vec2 z0, glm::vec2 constant, int max_iterations);
};

#endif