#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>

Camera::Camera(GLFWwindow* window) {
	this->window = window;
	fov = 45.0f;
	position = glm::vec3(0, 0, 5);
	mouseSpeed = 0.001f;
	yaw = 3.14f;
	pitch = 0.0f;
}

void Camera::computeMatrices() {
	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);

	if (glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
		yaw += mouseSpeed * float(windowWidth / 2 - xPos);
		float dPitch = mouseSpeed * float(windowHeight / 2 - yPos);
		if(pitch + dPitch <= 1.57 && pitch + dPitch >= -1.57)
			pitch += dPitch;
	}

	glm::vec3 direction(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
	glm::vec3 right = glm::vec3(sin(yaw - 3.14f / 2.0f), 0, cos(yaw - 3.14f / 2.0f));
	glm::vec3 up = glm::cross(right, direction);

	float speed = 3.0f;

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += direction * deltaTime * speed;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= direction * deltaTime * speed;
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += right * deltaTime * speed;
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= right * deltaTime * speed;

	projectionMatrix = glm::perspective(glm::radians(fov), (float) windowWidth / (float) windowHeight, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(position, position + direction, up);

	lastTime = currentTime;
}