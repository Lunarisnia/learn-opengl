#include "shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
  // 1. retrieve the vertex/fragment source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // ensure ifstream can throw exceptions???
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // Open files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer content into a stream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file header's
    vShaderFile.close();
    fShaderFile.close();
    // Convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
  }
  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();

  // Compile vertex shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vShaderCode, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // Compile fragment shader
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // Create the shader program
  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
              << infoLog << std::endl;
  }
  // We don't need it anymore, we can free the memory
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);
}

void Shader::use() { glUseProgram(ID); }

void Shader::setFloat(const std::string &name, float value) const {
  unsigned int location = glGetUniformLocation(ID, name.c_str());
  glUniform1f(location, value);
}

void Shader::setBool(const std::string &name, bool value) const {
  unsigned int location = glGetUniformLocation(ID, name.c_str());
  glUniform1i(location, (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
  unsigned int location = glGetUniformLocation(ID, name.c_str());
  glUniform1i(location, value);
}
