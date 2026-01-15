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

Capsule getPlayerCapsule(const glm::vec3& position) {
	return {
		position,
		position + glm::vec3(0.0f, playerHeight, 0.0f),
		playerRadius
	};
}

AABB getCubeAABB(const glm::vec3& position, float halfsize) {
	return {
		position - glm::vec3(halfsize),
		position + glm::vec3(halfsize)
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

bool capsuleAABBCollision(const Capsule& capsule, const AABB& box) {
	glm::vec3 segmentStart = capsule.base;
	glm::vec3 segmentEnd = capsule.tip;

	float sqDist = FLT_MAX;

	glm::vec3 closestPoint;
	closestPoint.x = glm::clamp(segmentStart.x, box.min.x, box.max.x);
	closestPoint.y = glm::clamp(segmentStart.y, box.min.y, box.max.y);
	closestPoint.z = glm::clamp(segmentStart.z, box.min.z, box.max.z);

	glm::vec3 difference = closestPoint - segmentStart;
	float squaredDistance = glm::dot(difference, difference);

	return squaredDistance <= (capsule.radius * capsule.radius);
}