#ifndef GAME_H
#define GAME_H

#include "Object.h"
#include "Model.h"
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
};

#endif