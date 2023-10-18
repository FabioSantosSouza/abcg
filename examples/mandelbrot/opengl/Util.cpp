#include "Util.hpp"

float mod2(glm::vec2 z) { return z.x * z.x + z.y * z.y; }

glm::vec2 computeNext(glm::vec2 current, glm::vec2 constant) {
  // quadrado do numero complexo
  const float zr = current.x * current.x - current.y * current.y;
  const float zi = 2.0f * current.x * current, y;
  // adicao da constante
  return glm::vec2{zr, zi} + constant;
}

int computeIteractions(glm::vec2 z0, glm::vec2 constant, int max_iterations) {
  glm::vec2 zn = z0;

  int iteration = 0;

  while (mod2(zn) < 4 && iteration < max_iterations) {
    zn = computeNext(zn, constant);
    iteration++;
  }
  return iteration;

  // como deixar os pixels suaves
  // const float mod = sqrt(mod2(zn));
  // const float smooth_iteration = gsl::narrow<float>(i) -
  // log2(max(1.0f,log2(mod))); return smooth_iteration;
}

// void render(glm::ivec2 render_size, glm::vec2 constant) {
//   const float scale = 1.0f / gsl::narrow<float>(render_size.y / 2);
//   for (int y{0}; y < render_size.y; y++) {
//     for (int x{0}; x < render_size.x; x++) {
//      const float px = gsl::narrow<float>(x - render_size.x / 2) * scale;
//      const float py = gsl::narrow<float>(y - render_size.y);
//      const float iteractios = computeIteractions({px, py}, constant, 50); //
//      50 eu quecontrololado
//       // AGORA EU PRECIO CONFIGURAR A COR DE CADA PIXEL
//       // setPixelColor(x,y, gradient.getcolor(iteracao))
//     }
//   }//
// }