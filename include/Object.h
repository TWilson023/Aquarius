#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>

#include "Renderable.h"

class Object {
	public:
		Object(Renderable* renderable, glm::vec3 position);
		Renderable* renderable;
		glm::vec3 position;
		void render(glm::mat4 mvp);
};

#endif