// #include "window.hpp"

// void Window::onCreate() {
//   // Enable Z-buffer test
//   abcg::glEnable(GL_DEPTH_TEST);

//   // Create shader program
//   auto const path{abcg::Application::getAssetsPath()};
//   m_program =
//       abcg::createOpenGLProgram({{.source = path + "UnlitVertexColor.vert",
//                                   .stage = abcg::ShaderStage::Vertex},
//                                  {.source = path + "UnlitVertexColor.frag",
//                                   .stage = abcg::ShaderStage::Fragment}});

//   // clang-format off
//   std::array const vertices{glm::vec2(0.0f, 0.5f),
//                             glm::vec2(0.5f, -0.5f),
//                             glm::vec2(-0.5f, -0.5f)};
//   std::array const colors{glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
//                           glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
//                           glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)};
//   // clang-format on

//   // Generate a new VBO and get the associated ID
//   abcg::glGenBuffers(1, &m_vboVertices);
//   // Bind VBO in order to use it
//   abcg::glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);
//   // Upload data to VBO
//   abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
//                      GL_STATIC_DRAW);
//   // Unbinding the VBO is allowed (data can be released now)
//   abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

//   abcg::glGenBuffers(1, &m_vboColors);
//   abcg::glBindBuffer(GL_ARRAY_BUFFER, m_vboColors);
//   abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors.data(),
//                      GL_STATIC_DRAW);
//   abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

//   // Get location of attributes in the program
//   auto const positionAttribute{
//       abcg::glGetAttribLocation(m_program, "inPosition")};
//   auto const colorAttribute{abcg::glGetAttribLocation(m_program, "inColor")};

//   // Create VAO
//   abcg::glGenVertexArrays(1, &m_vao);

//   // Bind vertex attributes to current VAO
//   abcg::glBindVertexArray(m_vao);

//   abcg::glEnableVertexAttribArray(positionAttribute);
//   abcg::glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);
//   abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
//                               nullptr);
//   abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

//   abcg::glEnableVertexAttribArray(colorAttribute);
//   abcg::glBindBuffer(GL_ARRAY_BUFFER, m_vboColors);
//   abcg::glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, 0,
//                               nullptr);
//   abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

//   // End of binding to current VAO
//   abcg::glBindVertexArray(0);
// }

// void Window::onPaint() {
//   // Set the clear color
//   abcg::glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b,
//                      m_clearColor.a);
//   // Clear the color buffer and Z-buffer
//   abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//   // Adjust viewport
//   abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

//   // Start using the shader program
//   abcg::glUseProgram(m_program);
//   // Start using the VAO
//   abcg::glBindVertexArray(m_vao);

//   // Render a triangle
//   abcg::glDrawArrays(GL_TRIANGLES, 0, 3);

//   // End using the VAO
//   abcg::glBindVertexArray(0);
//   // End using the shader program
//   abcg::glUseProgram(0);
// }

// void Window::onPaintUI() {
//   // Parent class will show fullscreen button and FPS meter
//   abcg::OpenGLWindow::onPaintUI();

//   // Our own ImGui widgets go below
//   {
//     // If this is the first frame, set initial position of our window
//     static auto firstTime{true};
//     if (firstTime) {
//       ImGui::SetNextWindowPos(ImVec2(5, 75));
//       firstTime = false;
//     }

//     // Window begin
//     ImGui::Begin("Hello! This is a Dear ImGui window");

//     // Static text
//     ImGui::Text("Some example widgets are given below.");

//     // Combo box
//     {
//       static auto currentIndex{0U};
//       std::vector<std::string> const comboItems{"First item", "Second item",
//                                                 "Third item", "Fourth item"};

//       if (ImGui::BeginCombo("A combo box",
//                             comboItems.at(currentIndex).c_str())) {
//         for (auto const index : iter::range(comboItems.size())) {
//           bool const isSelected{currentIndex == index};
//           if (ImGui::Selectable(comboItems.at(index).c_str(), isSelected))
//             currentIndex = index;

//           // Set the initial focus when opening the combo (scrolling +
//           keyboard
//           // navigation focus)
//           if (isSelected)
//             ImGui::SetItemDefaultFocus();
//         }
//         ImGui::EndCombo();
//       }
//     }

//     // Edit bools storing our window open/close state
//     ImGui::Checkbox("Show demo window", &m_showDemoWindow);
//     ImGui::Checkbox("Show another window", &m_showAnotherWindow);

//     // Slider from 0.0f to 1.0f
//     static auto value{0.0f};
//     ImGui::SliderFloat("A slider", &value, 0.0f, 1.0f);

//     // Edit background color
//     ImGui::ColorEdit3("Background", &m_clearColor.r);

//     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
//                 1000.0 / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

//     // End of window
//     ImGui::End();

//     // Show the big demo window (Most of the sample code is in
//     // ImGui::ShowDemoWindow()! You can browse its code to learn more about
//     Dear
//     // ImGui!).
//     if (m_showDemoWindow) {
//       ImGui::ShowDemoWindow(&m_showDemoWindow);
//     }

//     // Show another simple window
//     if (m_showAnotherWindow) {
//       // Pass a pointer to our bool variable (the window will have a closing
//       // button that will clear the bool when clicked)
//       ImGui::Begin("Another window", &m_showAnotherWindow);
//       ImGui::Text("Hello from another window!");
//       if (ImGui::Button("Close Me"))
//         m_showAnotherWindow = false;
//       ImGui::End();
//     }
//   }
// }

// void Window::onResize(glm::ivec2 const &size) { m_viewportSize = size; }

// void Window::onDestroy() {
//   // Release OpenGL resources
//   abcg::glDeleteProgram(m_program);
//   abcg::glDeleteBuffers(1, &m_vboVertices);
//   abcg::glDeleteBuffers(1, &m_vboColors);
//   abcg::glDeleteVertexArrays(1, &m_vao);
// }

#include "window.hpp"

void Window::onCreate() {
  auto const *vertexShader{R"gl(#version 300 es
    layout(location = 0) in vec2 inPosition;

    void main() {
      gl_PointSize = 1.0;
      gl_Position = vec4(inPosition, 0, 1); 
    }
  )gl"};

  // auto const *fragmentShader{R"gl(#version 300 es
  //   precision mediump float;

  //   out vec4 outColor;

  //   void main() { outColor = vec4(1); }
  // )gl"};

  auto const *fragmentShader{R"gl(#version 300 es

precision mediump float;
in vec4 gl_FragCoord;

uniform vec2 viewportSize;

uniform float constantRealPart;
uniform float constantImagPart;

uniform float maxIterR;
uniform float maxIterG;
uniform float maxIterB;

out vec4 frag_color;


#define MAX_ITERATIONS 500

int get_iterations() {
  //vec2 normalizedCoords = gl_FragCoord.xy / viewportSize;
float real = (2.0 * (gl_FragCoord.x / 600.0) - 1.0);
float imag = (2.0 * (gl_FragCoord.y / 600.0) - 1.0);

  int iterations = 0;
  float const_real = real;
  float const_imag = imag;

  while (iterations < MAX_ITERATIONS) {
    float tmp_real = real;
    real = (real * real - imag * imag) + constantRealPart;
    imag = (2.0 * tmp_real * imag) + constantImagPart;

    float dist = real * real + imag * imag;

    if (dist > 4.0)
      break;

    ++iterations;
  }
  return iterations;
}

vec4 return_color()
{
    int iter = get_iterations();
    if (iter == MAX_ITERATIONS)
    {
        //gl_FragDepth = 0.0f;
        return vec4(maxIterR, maxIterG, maxIterB, 1.0f);
    }
 
    float f_iter = float(iter);
    float f_max_iter = float(MAX_ITERATIONS);
    float iterations = f_iter / f_max_iter;

 
    vec4 color_0 = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec4 color_1 = vec4(0.0f, 0.2f, 0.5f, 1.0f);
    vec4 color_2 = vec4(1.0f, 0.8f, 0.0f, 1.0f);
    vec4 color_3 = vec4(1.0f, 0.0f, 0.4f, 1.0f);
 
    float fraction = 0.0f;
    if (iterations < 0.33333f)
    {
        fraction = (iterations - 0.0001f) / (0.33333f- 0.0001f);
        return mix(color_0, color_1, fraction);
    }
    else if(iterations < 0.66667f)
    {
        fraction = (iterations - 0.33333f) / (0.66667f - 0.33333f);
        return mix(color_1, color_2, fraction);
    }
    else
    {
        fraction = (iterations - 0.66667f) / (1.0f - 0.66667f);
        return mix(color_2, color_3, fraction);
    }
}

void main() { 
//float real = (2.0 * (gl_FragCoord.x / 600.0) - 1.0);
//float imag = (2.0 * (gl_FragCoord.y / 600.0) - 1.0);
 //frag_color = vec4(real,imag,0,1);
  frag_color = return_color();
  })gl"};

  // Create shader program
  m_program = abcg::createOpenGLProgram(
      {{.source = vertexShader, .stage = abcg::ShaderStage::Vertex},
       {.source = fragmentShader, .stage = abcg::ShaderStage::Fragment}});

  constant_real_part =
      abcg::glGetUniformLocation(m_program, "constantRealPart");
  constant_imag_part =
      abcg::glGetUniformLocation(m_program, "constantImagPart");

  max_iter_r = abcg::glGetUniformLocation(m_program, "maxIterR");
  max_iter_g = abcg::glGetUniformLocation(m_program, "maxIterG");
  max_iter_b = abcg::glGetUniformLocation(m_program, "maxIterB");

  // Clear window
  abcg::glClearColor(1, 1, 1, 1);
  abcg::glClear(GL_COLOR_BUFFER_BIT);

  std::array<GLfloat, 2> sizes{};
#if !defined(__EMSCRIPTEN__)
  abcg::glEnable(GL_PROGRAM_POINT_SIZE);
  abcg::glGetFloatv(GL_POINT_SIZE_RANGE, sizes.data());
#else
  abcg::glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, sizes.data());
#endif
  fmt::print("Point size: {:.2f} (min), {:.2f} (max)\n", sizes.at(0),
             sizes.at(1));
}

// void Window::onPaint() {
//   // Randomly pick the index of a triangle vertex
//   std::uniform_int_distribution<int> intDistribution(0, m_points.size() - 1);
//   auto const index{intDistribution(m_randomEngine)};

//   // The new position is the midpoint between the current position and the
//   // chosen vertex position
//   m_P = (m_P + m_points.at(index)) / 2.0f;

//   // Print coordinates to console
//   // fmt::print("({:+.2f}, {:+.2f})\n", m_P.x, m_P.y);
// }

void Window::onPaint() {

  if (m_timer.elapsed() < m_delay / 1000.0)
    return;
  m_timer.restart();
  // Set the clear color
  abcg::glClearColor(m_clearColor.at(0), m_clearColor.at(1), m_clearColor.at(2),
                     m_clearColor.at(3));
  // Clear the color buffer
  abcg::glClear(GL_COLOR_BUFFER_BIT);

  // Create OpenGL buffers for drawing the point at m_P

  setupModel();

  // Set the viewport
  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  // Start using the shader program
  abcg::glUseProgram(m_program);

  abcg::glUniform1f(constant_real_part, real_part);
  abcg::glUniform1f(constant_imag_part, imag_part);

  abcg::glUniform1f(max_iter_r, m_clearColor.at(0));
  abcg::glUniform1f(max_iter_g, m_clearColor.at(1));
  abcg::glUniform1f(max_iter_b, m_clearColor.at(2));

  // Start using VAO
  abcg::glBindVertexArray(m_VAO);

  // Draw a single point
  abcg::glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  // End using VAO
  abcg::glBindVertexArray(0);
  // End using the shader program
  abcg::glUseProgram(0);

  if (animate_real) {
    if (real_acumulator > -2.0f) {
      real_acumulator = real_part;
      real_acumulator -= 0.0001;
    } else {
      real_acumulator = 0.5;
    }
    real_part = real_acumulator;
  }
  if (animate_imag) {
    if (imag_acumulator < 2.0f) {
      imag_acumulator = imag_part;
      imag_acumulator += 0.001;
    } else {
      imag_acumulator = -2.0;
    }
    imag_part = imag_acumulator;
  }
}

// void Window::onPaint() {
//  Create OpenGL buffers for drawing the point at m_P
//  setupModel();

// Set the viewport
//  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

// Start using the shader program
//  abcg::glUseProgram(m_program);
// Start using VAO
//  abcg::glBindVertexArray(m_VAO);

// Draw a single point
//  abcg::glDrawArrays(GL_POINTS, 0, 1);

// End using VAO
//  abcg::glBindVertexArray(0);
// End using the shader program
//  abcg::glUseProgram(0);

// // Randomly pick the index of a triangle vertex
// std::uniform_int_distribution<int> intDistribution(0, m_points.size() - 1);
// auto const index{intDistribution(m_randomEngine)};

// // The new position is the midpoint between the current position and the
// // chosen vertex position
// m_P = (m_P + m_points.at(index)) / 2.0f;
// auto b = 0.0003f;

// if (angle <= 360.0f) {
//   m_P.x = sin(angle * M_1_PI / 180);
//   m_P.y = cos(angle * M_1_PI / 180);
//  angle += 0.001;
//  fmt::print("({:+.2f})\n", angle);
//  // fmt::print("({:+.2f}, {:+.2f})\n", m_P.x, m_P.y);
//  m_P.y += 0.000001;
//} else if (angle > 360.0f) {
// angle = 0.0f;
//}
// fmt::print("({:+.2f}, {:+.2f})\n", m_P.x, m_P.y);

// Print coordinates to console
// fmt::print("({:+.2f}, {:+.2f})\n", m_P.x, m_P.y);
//}

void Window::setupModel() {
  // Release previous VBO and VAO
  abcg::glDeleteBuffers(1, &m_VBOVertices);
  abcg::glDeleteVertexArrays(1, &m_VAO);

  // Generate a new VBO and get the associated ID
  abcg::glGenBuffers(1, &m_VBOVertices);
  // Bind VBO in order to use it
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOVertices);
  // Upload data to VBO
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(vetex), vetex.data(),
                     GL_STATIC_DRAW);
  // Unbinding the VBO is allowed (data can be released now)
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  auto const positionAttribute{
      abcg::glGetAttribLocation(m_program, "inPosition")};

  // Create VAO
  abcg::glGenVertexArrays(1, &m_VAO);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(m_VAO);

  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOVertices);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);
}

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;

  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::onDestroy() {
  // Release shader program, VBO and VAO
  abcg::glDeleteProgram(m_program);
  abcg::glDeleteBuffers(1, &m_VBOVertices);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}

void Window::onPaintUI() {
  // Parent class will show fullscreen button and FPS meter
  abcg::OpenGLWindow::onPaintUI();

  // Our own ImGui widgets go below
  {
    // Window begin
    ImGui::Begin("Option");
    ImGui::PushItemWidth(300);
    ImGui::SliderFloat("Real part (Cr)", &real_part, -2.0f, 0.5f);
    ImGui::PopItemWidth();
    ImGui::PushItemWidth(300);
    ImGui::SliderFloat("Imaginary part (Ci)", &imag_part, -2.0f, 2.0f);
    ImGui::PopItemWidth();

    ImGui::ColorEdit3("Change Max Color", m_clearColor.data());

    ImGui::Checkbox("vary real part (Cr)", &animate_real);

    ImGui::Checkbox("vary imag.. part (Ci)", &animate_imag);

    ImGui::PushItemWidth(140);
    ImGui::SliderInt("Delay", &m_delay, 0, 200, "%d ms");
    ImGui::PopItemWidth();
    // More static text
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0 / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    // Window end
    ImGui::End();
  }
}

float Window::mod2(glm::vec2 z) { return z.x * z.x + z.y * z.y; }

glm::vec2 Window::computeNext(glm::vec2 current, glm::vec2 constant) {
  // quadrado do numero complexo
  const float zr = current.x * current.x - current.y * current.y;
  const float zi = 2.0f * current.x * current.y;
  // adicao da constante
  return glm::vec2{zr, zi} + constant;
}

int Window::computeIteractions(glm::vec2 z0, glm::vec2 constant,
                               int max_iterations) {
  glm::vec2 zn = z0;

  int iteration = 0;

  while (Window::mod2(zn) < 4 && iteration < max_iterations) {
    zn = Window::computeNext(zn, constant);
    iteration++;
  }
  return iteration;
}
// como deixar os pixels suaves
// const float mod = sqrt(mod2(zn));
// const float smooth_iteration = gsl::narrow<float>(i) -
// log2(max(1.0f,log2(mod))); return smooth_iteration;