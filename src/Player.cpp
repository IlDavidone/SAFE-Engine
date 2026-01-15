#include "Player.h"

const float playerRadius = 0.5f;
const float playerHeight = 1.8f;

const Camera& Player::getCamera() const {
	return m_playerCamera;
}

const glm::vec3& Player::getPosition() {
	return m_position;
}

void Player::setPosition(float x, float y, float z) {
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void Player::setPosition(glm::vec3 position) {
	m_position = position;
}

float Player::getHealth() const {
	return m_health;
}

void Player::setHealth(float health) {
	m_health = health;
}

float Player::getSpeed() const {
	return m_speed;
}

void Player::setSpeed(float speed) {
	m_speed = speed;
}

void updatePlayerPhysics(Player& player, float& yPosVelocity, float deltaTime, std::vector<AABB>& worldAABBs) {
	glm::vec3 pos = player.getPosition();
	glm::vec3 camForward = glm::normalize(glm::vec3(player.getCamera().Front.x, 0.0f, player.getCamera().Front.z));
	glm::vec3 camRight = glm::normalize(glm::cross(camForward, glm::vec3(0.0f, 1.0f, 0.0f)));

	float playerSpeed = player.getSpeed();
	
	glm::vec3 moveDir(0.0f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) moveDir += camForward;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) moveDir -= camForward;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) moveDir -= camRight;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) moveDir += camRight;

	if (glm::length(moveDir) > 0.0f)
		moveDir = glm::normalize(moveDir);

	xVelocity = moveDir.x * playerSpeed;
	zVelocity = moveDir.z * playerSpeed;

	yPosVelocity -= gravityAcceleration * deltaTime;

	glm::vec3 deltaPos = glm::vec3(xVelocity * deltaTime, yPosVelocity * deltaTime, zVelocity * deltaTime);
	pos.y += deltaPos.y;

	Capsule playerCapsule = getPlayerCapsule(pos);

	glm::vec3 newPos = pos;

	AABB box = getPlayerAABB(pos);
	if (checkGroundCollision(box)) {
		newPos.y -= box.min.y;
		yPosVelocity = 0.0f;
	}

	newPos.x += deltaPos.x;
	playerCapsule = getPlayerCapsule(newPos);
	for(const auto& box : worldAABBs) {
		if (capsuleAABBCollision(playerCapsule, box)) {
			newPos.x = pos.x;
			xVelocity = 0.0f;
			break;
		}
	}

	newPos.z += deltaPos.z;
	playerCapsule = getPlayerCapsule(newPos);
	for (const auto& box : worldAABBs) {
		if (capsuleAABBCollision(playerCapsule, box)) {
			newPos.z = pos.z;
			zVelocity = 0.0f;
			break;
		}
	}

	player.setPosition(newPos);
}
