//
// Created by kamil on 18.09.23.
//
#define STB_IMAGE_IMPLEMENTATION

#include "./glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <exception>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders/shader.hpp"
#include "shaders/VBO.hpp"
#include "shaders/VAO.hpp"
#include "shaders/EBO.hpp"
#include "shaders/texture.hpp"
#include "shaders/camera.h"
#include "obj/light.hpp"
#include "obj/block.h"
#include "voxel/voxel_grid.hpp"

const unsigned int width = 800;
const unsigned int height = 800;

int main(int argc, char *argv[]) {

    if(argc<4){
        std::cerr<<"Usage ./voxel_rendering x y z\n";
        return -1;
    }
    std::cout << argv[1];
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, width, height);

    Shader shaderProgram("../shaders/default.vert", "../shaders/default.frag");
    Texture textures[] = {
            Texture("../grass.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE),
            Texture("../grass.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };
    std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

    Light lightObj(tex,glm::vec3((std::stof(argv[2])/2)/5.,std::stoi(argv[2])/2,(std::stof(argv[3])/2.)/5.));

    //Block block(glm::vec3(1.f));


    std::vector<Vertex> verts(vertices, vertices + sizeof(vertices)/sizeof(Vertex));
    std::vector<GLuint> ind(indices,indices+sizeof(indices)/sizeof(GLuint));

    Mesh mesh(verts, ind, tex);

    VoxelGrid grid(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]), mesh);

    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));



    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        grid.DrawVoxelGrid(shaderProgram, lightObj, camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}