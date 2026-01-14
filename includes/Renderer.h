#pragma once

#include "Includes.h"

class Model;
class Player;

class Renderer {
public: 
	Renderer() = default;

	void DrawModel(Model& model, const glm::mat4& modelMatrix, Shader& shader);
	void DrawPlayer(const Player& player, Model& playerModel, Shader& shader, glm::mat4& projection, glm::mat4& view);
};