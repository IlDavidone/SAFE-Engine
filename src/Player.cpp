#include "Player.h"

const float playerRadius = 0.3f;
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

void updatePlayerPhysics(Player& player, float& yPosVelocity, float deltaTime) {
	glm::vec3 pos = player.getPosition();

	yPosVelocity -= gravityAcceleration * deltaTime;

	glm::vec3 deltaPos = glm::vec3(0.0f, yPosVelocity * deltaTime, 0.0f);
	pos.y += deltaPos.y;

	AABB box = getPlayerAABB(pos);
	if (checkGroundCollision(box)) {
		pos.y -= box.min.y;
		yPosVelocity = 0.0f;
	}

	player.setPosition(pos);
}
