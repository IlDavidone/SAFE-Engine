#ifndef GLOBALS_H
#define GLOBALS_H

#include "includes.h"

namespace pixel {
	constexpr uint16_t width{ 1536 };
	constexpr uint16_t height{ 864 };
}

extern GLFWwindow* window;

extern float vertices[];
extern unsigned int verticesSize;

extern glm::vec3 cubePositions[];

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

#endif