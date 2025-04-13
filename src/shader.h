#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
  // The program ID
  unsigned int ID;

  // Constructor that reads and builds the shader
  Shader(const char *vertexPath, const char *fragmentPath);
  // Use/activate the shader
  void use();

  // Utility function for uniforms
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setMat4(const std::string &name, glm::mat4 value) const;
};

#endif
