#ifndef GAME_H
#define GAME_H

#include "Model.h"
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
		Model* model;
};

#endif