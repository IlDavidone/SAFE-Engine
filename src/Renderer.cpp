#include "Renderer.h"

void Renderer::DrawModel(Model& model, const glm::mat4& modelMatrix, Shader& shader) {
    shader.Activate();
    glUniformMatrix4fv(
        glGetUniformLocation(shader.ID, "model"),
        1, GL_FALSE,
        glm::value_ptr(modelMatrix)
    );
    model.Draw(shader);
}

void Renderer::DrawPlayer(const Player& player, Model& playerModel, Shader& shader, glm::mat4& projection, glm::mat4& view) {
    shader.Activate();
    const Camera& camera = player.getCamera();

    glUniform1f(glGetUniformLocation(shader.ID, "time"), glfwGetTime());
    glUniform1f(glGetUniformLocation(shader.ID, "health"), player.getHealth());
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniform3f(glGetUniformLocation(shader.ID, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    glUniform1i(glGetUniformLocation(shader.ID, "material.diffuse"), 0);
    glUniform3f(glGetUniformLocation(shader.ID, "objectColor"), 1.0f, 1.0f, 1.0f);

    //specific for floating arms model
    model = glm::mat4(1.0f);
    model = glm::translate(model, camera.Position);
    model *= glm::inverse(glm::mat4(glm::mat3(view)));
    model = glm::translate(model, glm::vec3(0.0f, -0.3f, -0.5f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, sin(glfwGetTime() * 2.6f) / 46));

    glUniformMatrix4fv(
        glGetUniformLocation(shader.ID, "model"),
        1, GL_FALSE,
        glm::value_ptr(model)
    );

    playerModel.Draw(shader);
}