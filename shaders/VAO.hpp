#ifndef VAO_H_
#define VAO_H_
#include "../glad/glad.h"
#include "./VBO.hpp"
class VAO
{
public:
    GLuint ID;
    VAO();

    void LinkAttrib(VBO& VBO, GLuint layout,
                    GLuint numC, GLenum type,
                    GLsizeiptr stride, void *offset);
    void Bind();
    void Unbind();
    void Delete();
};

#endif