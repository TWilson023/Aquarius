#ifndef CAMERA_H
#define CAMERA_H

#include <glfw3.h>
#include <glm/glm.hpp>

class Camera {
	public:
		Camera(GLFWwindow* window);
		float pitch, yaw, fov;
		float mouseSpeed;
		glm::vec3 position;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		void computeMatrices();
	private:
		GLFWwindow* window;
};

#endif