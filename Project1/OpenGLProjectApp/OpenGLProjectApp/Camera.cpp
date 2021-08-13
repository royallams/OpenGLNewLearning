#include "Camera.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;// Initially we consider the world up position.
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);// consider the front with z

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;// Deltatime = diff in the time since moved.

	if (keys[GLFW_KEY_W])// Go front, veocity = sensitivity 
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S])// Come back
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A])// Go left 
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])// Go right
	{
		position += right * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;// Move based on the position.			
	yChange *= turnSpeed;

	yaw += xChange;// yaw is rotating in x 
	pitch += yChange;// Pitch is in y 

	if (pitch > 89.0f)// Keep it within the window 
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);// Take the latest position , where looking at and up to get viewmatrix
}

void Camera::update()
{
	// Get the front from the angles.
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	// Calculate the right from the cross prod.. with the world.
	right = glm::normalize(glm::cross(front, worldUp));

	// Calculate the current up with the cross of the right and the front.
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera()
{
}
