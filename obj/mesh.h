//
// Created by kamil on 19.09.23.
//

#ifndef UI_CREATOR_MESH_H
#define UI_CREATOR_MESH_H

#include <string>
#include <memory>
#include "../shaders/VAO.hpp"
#include "../shaders/EBO.hpp"
#include "../shaders/camera.h"
#include "../shaders/texture.hpp"

class Mesh: public std::enable_shared_from_this<Mesh> {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    VAO _VAO;
public:
    Mesh(std::vector<Vertex> &_vertices, std::vector<GLuint> &_indices,
         std::vector<Texture> &_textures);
    Mesh() { ; }
    void Draw(Shader &shader, Camera &camera);
};


#endif //UI_CREATOR_MESH_H
