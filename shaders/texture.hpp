#ifndef TEXTURE_H
#define TEXTURE_H


#include <string>
#include "../glad/glad.h"
#include "shader.hpp"
#include "../stb/stb_image.h"

class Texture
{
public:
    GLuint ID;
    const char* type;
    GLuint unit;

    Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);

    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
};
#endif


