#include "./VAO.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO &VBO, GLuint layout,
                     GLuint numC, GLenum type,
                     GLsizeiptr stride, void *offset)
{
    VBO.Bind();
    glVertexAttribPointer(layout, numC, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}
void VAO::Bind()
{
    glBindVertexArray(ID);
}
void VAO::Unbind()
{
    glBindVertexArray(0);
}
void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}