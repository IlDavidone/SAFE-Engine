#pragma once

#include "Includes.h"

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

		const Camera& getCamera() const {
			return m_playerCamera;
		}

		const glm::vec3& getPosition() {
			return m_position;
		}
		void setPosition(float x, float y, float z) {
			m_position.x = x;
			m_position.y = y;
			m_position.z = z;
		}
		void setPosition(glm::vec3 position) {
			m_position = position;
		}

		float getHealth() const {
			return m_health;
		}
		void setHealth(float health) {
			m_health = health;
		}

		float getSpeed() const {
			return m_speed;
		}
		void setSpeed(float speed) {
			m_speed = speed;
		}
};