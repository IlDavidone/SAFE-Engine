#pragma once

#include "Includes.h"

class Player {
	glm::vec3 m_position;
	Camera& m_playerCamera;
	uint8_t m_speed;

	public:
		Player(Camera& camera, glm::vec3& cameraPosition) : m_playerCamera(camera), m_position(cameraPosition), m_speed(2) {}
		~Player() = default;

		Player(const Player&) = default;
		Player& operator=(const Player&) = delete;

		const Camera& getCamera() const {
			return m_playerCamera;
		}

		const glm::vec3& getPosition() {
			return m_position;
		}
		void setPosition(glm::vec3 position) {
			m_position = position;
		}

		uint8_t getSpeed() const {
			return m_speed;
		}
		void setSpeed(uint8_t speed) {
			m_speed = speed;
		}
};