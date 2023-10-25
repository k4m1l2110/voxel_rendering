//
// Created by kamil on 08.10.23.
//
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

#include "./shaders/shader.hpp"
#include "./shaders/VBO.hpp"
#include "./shaders/VAO.hpp"
#include "./shaders/EBO.hpp"
#include "./shaders/texture.hpp"
#include "./shaders/camera.h"
#include "./misc/mesh.h"
#include "./misc/block.h"

const unsigned int width = 800;
const unsigned int height = 800;


Vertex lightVertices[] =
        { //     COORDINATES     //
                Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
                Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
                Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
                Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
                Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
                Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
                Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
                Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
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

int main()
{


    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
    GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, width, height);

    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("../shaders/default.vert", "../shaders/default.frag");
    Texture textures[] = {
            Texture("../planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
            Texture("../planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };
    std::vector<Texture> tex(textures, textures+sizeof(textures)/sizeof(Texture));



    // Shader for light cube
    Shader lightShader("../shaders/light.vert", "../shaders/light.frag");
    std::vector<Vertex> l_verts(lightVertices, lightVertices + sizeof(lightVertices)/sizeof(Vertex));
    std::vector<GLuint> l_ind(lightIndices,lightIndices+sizeof(lightIndices)/sizeof(GLuint));
    Mesh light(l_verts,l_ind,tex);

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);


    BlockRenderer block;

    glEnable(GL_DEPTH_TEST);

    // Creates camera object
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Handles camera inputs
        camera.Inputs(window);
        // Updates and exports the camera matrix to the Vertex Shader
        camera.updateMatrix(45.0f, 0.1f, 100.0f);
        for(float i=0.;i<3.;i++)
        block.Draw(shaderProgram,lightShader,camera,glm::vec3(1.f,1.f,i));

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    shaderProgram.Delete();
    lightShader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}