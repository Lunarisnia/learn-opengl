#include <glad/glad.h>
// FORCE
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main() {\n"
                                 "  gl_Position = vec4(aPos, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(0.63, 0.43, 0.51, 1.0);\n"
    "}\0";

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
      0.5f, 0.5f, 0.0f,   // top right
      0.5f, -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
                          //
      -0.9f, 0.5f, 0.0f,  // top left
      -1.0f, -0.5f, 0.0f, // Bottom left
      -0.8f, -0.5f, 0.0f  // bottom right

  };
  // Setup for index based rendering using EBO
  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  // ======= Vertex Shader Setup ==============
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // ======= Vertex Shader Setup END ==========

  // ======= Fragment Shader Setup ==========
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  // ======= Fragment Shader Setup END ======

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
              << infoLog << std::endl;
  }

  // We don't need it anymore, we can free the memory
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);

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

  // Bind the EBO before setting the VBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Wireframe mode
    /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

    glUseProgram(shaderProgram);
    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/
    /*glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}
