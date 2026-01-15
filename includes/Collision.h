#pragma once

#include "Includes.h"

struct AABB {
	glm::vec3 min;
	glm::vec3 max;
};

struct Capsule {
	glm::vec3 base;
	glm::vec3 tip;
	float radius;
};

AABB getPlayerAABB(const glm::vec3& position);

Capsule getPlayerCapsule(const glm::vec3& position);

AABB getCubeAABB(const glm::vec3& position, float halfsize);

bool checkGroundCollision(const AABB& a);

bool checkAABBCollision(const AABB& a, const AABB& b);

bool capsuleAABBCollision(const Capsule& capsule, const AABB& box);