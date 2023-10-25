//
// Created by kamil on 18.09.23.
//

#ifndef UI_CREATOR_BLOCK_H
#define UI_CREATOR_BLOCK_H

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "../shaders/shader.hpp"
#include "../shaders/VBO.hpp"
#include "../shaders/VAO.hpp"
#include "../shaders/EBO.hpp"
#include "../shaders/texture.hpp"
#include "../shaders/camera.h"
#include "light.hpp"
#include "mesh.h"

static Vertex vertices[] = {
        //     COORDINATES                  /           COLORS          /           TexCoord           /       NORMALS     //
        // Front face
        Vertex{glm::vec3(-0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},

        // Back face
        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},

        // Left face
        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-0.1f, 0.1f, -0.1f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(-0.1f, 0.1f, 0.1f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(-0.1f, -0.1f, 0.1f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},

        // Right face
        Vertex{glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.1f, 0.1f, -0.1f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(0.1f, -0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},

        // Top face
        Vertex{glm::vec3(-0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},

        // Bottom face
        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-0.1f, -0.1f, 0.1f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(0.1f, -0.1f, 0.1f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
};
static GLuint indices[] =
        {
                // Front face
                0, 1, 2,
                2, 3, 0,

                // Back face
                4, 5, 6,
                6, 7, 4,

                // Left face
                8, 9, 10,
                10, 11, 8,

                // Right face
                12, 13, 14,
                14, 15, 12,

                // Top face
                16, 17, 18,
                18, 19, 16,

                // Bottom face
                20, 21, 22,
                22, 23, 20
        };

class Block {
public:
    glm::mat4 model;
    glm::vec3 position;  // Position of the voxel in the grid.
    Block(glm::vec3 pos, Mesh &meshPtr);
    void Draw(Shader& shader,Light &light, Camera& camera);
private:

    glm::mat4 modelMatrix;
    Mesh &mesh;
};

#endif //UI_CREATOR_BLOCK_H
