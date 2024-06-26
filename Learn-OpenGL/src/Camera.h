#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f; // YAW means Y-axis rotation
const float PITCH = 0.0f; // PITCH means X-axis rotation
const float SPEED = 700.0f; // camera speed
const float SENSITIVITY = 0.6f; // mouse sensitivity
const float ZOOM = 45.0f; // field of view

class Camera
{
private:
	// camera attributes
	glm::vec3 m_Position;
	glm::vec3 m_Up;
	glm::vec3 m_Front;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	// Euler angles
	float m_Yaw;
	float m_Pitch;

	// camera options
	float m_MovementSpeed;
	float m_MouseSensitivity;
	float m_Zoom;

public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
		: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM) 
	{
		m_Position = position;
		m_WorldUp = up;
		m_Yaw = yaw;
		m_Pitch = pitch;
		updateCameraVectors();
	};

	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM) 
	{
		m_Position = glm::vec3(posX, posY, posZ);
		m_WorldUp = glm::vec3(upX, upY, upZ);
		m_Yaw = yaw;
		m_Pitch = pitch;
		updateCameraVectors();
	};

	glm::mat4 GetViewMatrix() const;
	void ProcessKeyboard(CameraMovement direction, float deltaTime);
	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
	void ProcessMouseScroll(float yOffset);
	inline float getZoom() const { return m_Zoom; };
	
private:
	void updateCameraVectors();
};


