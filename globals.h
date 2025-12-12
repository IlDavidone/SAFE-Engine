#ifndef GLOBALS_H
#define GLOBALS_H

#include "includes.h"

namespace pixel {
	constexpr uint16_t width{ 1536 };
	constexpr uint16_t height{ 864 };
}

class Cube {
	public:
		GLuint ID;
		float rotationAngle;
		glm::vec3 position;
		
		Cube(GLuint ID, float rotationAngle, glm::vec3 position) : ID(ID), rotationAngle(rotationAngle), position(position) {}

		void draw(Shader& shader);
		void scaleCube(float scaleFactor);
		void positionCube(glm::vec3 newPosition);
		void rotateCube(float angle);
};

extern GLFWwindow* window;

extern float vertices[];
extern unsigned int verticesSize;

extern std::unique_ptr<std::vector<Cube>> cubePositions;

extern int framePerSeconds;

extern glm::mat4 model;
extern glm::mat4 view;
extern glm::mat4 projection;

extern glm::vec3 lightPos;

extern bool showDemoWindow;
extern bool movingLightBulb;

extern float deltaTime;
extern float lastFrame;
extern float currentFrame;

extern float lightPosSpeed;

extern struct lightProperties {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

extern lightProperties lightProps;

#endif