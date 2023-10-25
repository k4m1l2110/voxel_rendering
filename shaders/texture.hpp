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

    // Assigns a texture unit to a texture
    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    // Binds a texture
    void Bind();
    // Unbinds a texture
    void Unbind();
    // Deletes a texture
    void Delete();
};
#endif


