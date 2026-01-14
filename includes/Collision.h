#pragma once

#include "Includes.h"

struct AABB {
	glm::vec3 min;
	glm::vec3 max;
};

AABB getPlayerAABB(const glm::vec3& position);

bool checkGroundCollision(const AABB& a);

bool checkAABBCollision(const AABB& a, const AABB& b);