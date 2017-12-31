#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object.h"
#include "Model.h"
#include "planets/Planet.h"
#include "primitives/Cube.h"
#include "Camera.h"
#include "ShaderProgram.h"

class Game {
	public:
		Game(GLFWwindow* window);
		void init();
		void update();
		void render();
		ShaderProgram* simpleShader;
	private:
		Camera* camera;
		Object* object;
		Object* planetObject;
};

#endif