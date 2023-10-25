//
// Created by kamil on 18.09.23.
//

#ifndef UI_CREATOR_BLOCK_H
#define UI_CREATOR_BLOCK_H

#include <glm/glm.hpp>
#include <vector>
#include "../shaders/shader.hpp"
#include "../shaders/VBO.hpp"
#include "../shaders/VAO.hpp"
#include "../shaders/EBO.hpp"
#include "../shaders/texture.hpp"
#include "../shaders/camera.h"
#include "mesh.h"

class BlockRenderer {
public:
    BlockRenderer();
    void Draw(Shader& shader,Shader& lightShader, Camera& camera, glm::vec3 objectPos);

private:
    // Define properties of the block, such as vertices, indices, and textures
    glm::mat4 modelMatrix;
    Mesh mesh;
    // Other private methods for initializing and rendering the block
};

#endif //UI_CREATOR_BLOCK_H
