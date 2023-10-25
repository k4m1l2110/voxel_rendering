#ifndef SHADER_H_
#define SHADER_H_
#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <iostream>

std::string get_file_contents(const char* fn);

class Shader{
    public:
        GLuint ID;
        Shader(const char* vertexf, const char* fragmentf);
        void compileErrors(unsigned int shader, const char* type);
        void Activate();
        void Delete();
        void SetMatrix4(const std::string& name, const glm::mat4& matrix) const;
};

#endif