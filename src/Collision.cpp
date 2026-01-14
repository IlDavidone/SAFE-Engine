#include "Collision.h"

AABB getPlayerAABB(const glm::vec3& position) {
	return AABB{
		glm::vec3(
			position.x - playerRadius,
			position.y,
			position.z - playerRadius
		),
		glm::vec3(
			position.x + playerRadius,
			position.y + playerHeight,
			position.z + playerRadius
		)
	};
}

bool checkGroundCollision(const AABB& a) {
	return a.min.y <= 0.0f;
}

bool checkAABBCollision(const AABB& a, const AABB& b) {
	return (a.min.x <= b.max.x && a.max.x >= b.min.x) &&
		(a.min.y <= b.max.y && a.max.y >= b.min.y) &&
		(a.min.z <= b.max.z && a.max.z >= b.min.z);
}