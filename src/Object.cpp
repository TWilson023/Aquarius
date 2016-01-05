#include "Object.h"

Object::Object(Renderable* renderable, glm::vec3 position) {
	this->renderable = renderable;
	this->position = position;
}

void Object::render(glm::mat4 mvp) {
	renderable->render(mvp);
}