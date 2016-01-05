#include "Game.h"

#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Game::Game(GLFWwindow* window) {
	camera = new Camera(window);
}

void Game::init() {
	simpleShader = new ShaderProgram("shaders/simple.vert", "shaders/simple.frag");
	Texture* texture = new Texture();
	texture->loadDDS("res/cube.DDS");
	object = new Object(new Model("res/cube.obj", simpleShader), glm::vec3(0.0f, 0.0f, 0.0f));
}

void Game::update() {
	
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->computeMatrices();
	glm::mat4 projectionMatrix = camera->projectionMatrix;
	glm::mat4 viewMatrix = camera->viewMatrix;
	glm::mat4 modelMatrix = glm::mat4(1.0);
	glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

	object->render(mvp);
}