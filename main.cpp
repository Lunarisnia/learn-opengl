#include "src/shader.h"
#include <glad/glad.h>
// FORCE
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  std::cout << "resizing to: " << width << "x" << height << std::endl;
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

int main() {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // ============= GLFW Window Creation
  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW Window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // ============= GLAD Loading
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Vertices of a triangle
  float vertices[] = {
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f  // bottom left
  };

  Shader shaderProgram("./shaders/vertex-shader.vert",
                       "./shaders/fragment-shader.frag");

  Shader shaderProgram2("./shaders/vertex-shader.vert",
                        "./shaders/fragment-shader.frag");

  // We create a vertex buffer
  unsigned int VBO, VAO, EBO;
  glGenBuffers(1, &EBO);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // Bind the VAO before setting the VBO
  glBindVertexArray(VAO);

  // Bind the vertex buffer to a memory space in the GPU
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // Actually set the value of the vertex buffer on the GPU from the CPU
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  float vertices2[] = {
      1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Top right
      1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom right
      0.6f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // Bottom left
  };
  unsigned int VBO2, VAO2;
  glGenVertexArrays(1, &VAO2);
  glGenBuffers(1, &VBO2);
  glBindVertexArray(VAO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Color Attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
            << std::endl;

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Wireframe mode
    /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

    shaderProgram.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    shaderProgram2.use();
    glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/
    /*glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  /*glDeleteProgram(shaderProgram);*/

  glfwTerminate();
  return 0;
}
