#ifndef LIGHT_HPP_
#define LIGHT_HPP_
#include "mesh.h"

class Light {
public:
    Shader _shader;
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos;
    glm::mat4 lightModel = glm::mat4(1.0f);

    Light(std::vector<Texture> tex,glm::vec3 pos) :lightPos(pos), _shader("../shaders/light.vert", "../shaders/light.frag") {
        Vertex lightVertices[] =
                { //     COORDINATES     //
                        Vertex{glm::vec3(-0.1f, -0.1f, 0.1f)},
                        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
                        Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
                        Vertex{glm::vec3(0.1f, -0.1f, 0.1f)},
                        Vertex{glm::vec3(-0.1f, 0.1f, 0.1f)},
                        Vertex{glm::vec3(-0.1f, 0.1f, -0.1f)},
                        Vertex{glm::vec3(0.1f, 0.1f, -0.1f)},
                        Vertex{glm::vec3(0.1f, 0.1f, 0.1f)}
                };

        GLuint lightIndices[] =
                {
                        0, 1, 2,
                        0, 2, 3,
                        0, 4, 7,
                        0, 7, 3,
                        3, 7, 6,
                        3, 6, 2,
                        2, 6, 5,
                        2, 5, 1,
                        1, 5, 4,
                        1, 4, 0,
                        4, 5, 6,
                        4, 6, 7
                };
        std::vector<Vertex> l_verts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
        std::vector<GLuint> l_ind(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
        Mesh light(l_verts, l_ind, tex);

        lightModel = glm::translate(lightModel, lightPos);

        _shader.Activate();
        glUniformMatrix4fv(glGetUniformLocation(_shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
        glUniform4f(glGetUniformLocation(_shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z,
                    lightColor.w);
    }
    ~Light(){
        _shader.Delete();
    }
};

#endif