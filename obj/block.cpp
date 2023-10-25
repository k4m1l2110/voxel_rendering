//
// Created by kamil on 18.09.23.
//

#include "block.h"

Block::Block(glm::vec3 pos, Mesh &m): mesh(m),position(pos), model(glm::mat4(1.0f)) {
    model = glm::translate(model, position);
}

void Block::Draw(Shader& shader, Light &light, Camera& camera)
{
    shader.Activate();

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), light.lightColor.x, light.lightColor.y, light.lightColor.z, light.lightColor.w);
    glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), light.lightPos.x, light.lightPos.y, light.lightPos.z);

    mesh.Draw(shader,camera);
    mesh.Draw(light._shader, camera);
}

