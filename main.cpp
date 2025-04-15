#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include "src/shader.h"
#include "src/stb_image.h"
#include <glad/glad.h>
// FORCE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

float smileyTransparency = 0.2f;

// Creating Camera
// ========================
// Camera position
glm::vec3 cameraPos(0.0f, 0.0f, 3.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);

float yaw = -90.0f;
float pitch = 0.0f;

// Camera Target
/*glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);*/
// Direction to camera
/*glm::vec3 cameraDirection(cameraPos - cameraTarget);*/

// Camera Axis
/*glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));*/
/*glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection,
 * cameraRight));*/
// All that's left is create the view matrix but I am going to use a function
// provided by GLM

// Frame timing
// ======================
float deltaTime = 0.0f;
float currentFrame = 0.0f;
float lastFrame = 0.0f;

float lastX = 400.0f;
float lastY = 300.0f;

float fov = 45.0f;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  std::cout << "resizing to: " << width << "x" << height << std::endl;
  glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  float xOffset = xpos - lastX;
  float yOffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;

  const float sensitivity = 0.1f;
  xOffset *= sensitivity;
  yOffset *= sensitivity;

  yaw += xOffset;
  pitch += yOffset;
  if (pitch > 89.0f) {
    pitch = 89.0f;
  }
  if (pitch < -89.0f) {
    pitch = -89.0f;
  }

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  fov -= (float)yoffset;
  if (fov < 1.0f) {
    fov = 1.0f;
  }
  if (fov > 45.0f) {
    fov = 45.0f;
  }
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  const float cameraSpeed = 0.5f * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    smileyTransparency -= 0.1f;
  }
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    smileyTransparency += 0.1f;
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    cameraPos += cameraSpeed * cameraFront;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    cameraPos -= cameraSpeed * cameraFront;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    cameraPos -= glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    cameraPos += glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;
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

  // Vertices of a triangle forming a cube
  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

  Shader shaderProgram("./shaders/vertex-shader.vert",
                       "./shaders/texture-shader.frag");
  shaderProgram.use();
  shaderProgram.setFloat("horizontalOffset", 0.0f);

  // We create a vertex buffer
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // Bind the VAO before setting the VBO
  glBindVertexArray(VAO);

  // Bind the vertex buffer to a memory space in the GPU
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // Actually set the value of the vertex buffer on the GPU from the CPU
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Check max attribute allowed on hardware
  // =======================================
  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
            << std::endl;

  shaderProgram.use();
  shaderProgram.setInt("imageTexture", 0);
  shaderProgram.setInt("imageTexture2", 1);

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // Set texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Load & Generate Textures
  // =============
  int width, height, nrChannels;
  unsigned char *data =
      stbi_load("./textures/container.jpg", &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "ERROR::IMAGE_LOADING: failed to load textures" << std::endl;
  }
  stbi_image_free(data);

  unsigned int texture2;
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  stbi_set_flip_vertically_on_load(true);
  data =
      stbi_load("./textures/awesomeface.png", &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "ERROR::IMAGE_LOADING: failed to load textures" << std::endl;
  }
  stbi_image_free(data);

  // Enable depth buffer test
  glEnable(GL_DEPTH_TEST);

  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  // Capture the mouse
  // =======================
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  while (!glfwWindowShouldClose(window)) {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, up);

    glm::mat4 projection(1.0f);
    projection =
        glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::mat4 orthoProjection(1.0f);
    orthoProjection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Wireframe mode
    /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

    shaderProgram.use();
    shaderProgram.setFloat("transparency", smileyTransparency);
    shaderProgram.setMat4("view", view);
    shaderProgram.setMat4("projection", projection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glBindVertexArray(VAO);

    for (unsigned int i = 0; i < 10; i++) {
      glm::mat4 localModel(1.0f);
      localModel = glm::translate(localModel, cubePositions[i]);
      localModel = glm::rotate(localModel, glm::radians(i * 20.0f),
                               glm::normalize(glm::vec3(0.3f, 1.0f, 1.0f)));
      localModel =
          glm::rotate(localModel, (float)glfwGetTime() * glm::radians(-55.0f),
                      glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f)));
      shaderProgram.setMat4("model", localModel);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

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
