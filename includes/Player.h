#pragma once

#include "Includes.h"

extern const float playerRadius;
extern const float playerHeight;

class Player {
	glm::vec3 m_position;
	Camera& m_playerCamera;
	float m_health;
	float m_speed;

	public:
		Player(Camera& camera, glm::vec3& cameraPosition, float health) : m_playerCamera(camera), m_position(cameraPosition), m_health(health), m_speed(2.0f) {}
		~Player() = default;

		Player(const Player&) = default;
		Player& operator=(const Player&) = delete;

		const Camera& getCamera() const;

		const glm::vec3& getPosition();

		void setPosition(float x, float y, float z);

		void setPosition(glm::vec3 position);

		float getHealth() const;

		void setHealth(float health);

		float getSpeed() const;

		void setSpeed(float speed);
};

void updatePlayerPhysics(Player& player, float& yPosVelocity, float deltaTime);