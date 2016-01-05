#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <glm/glm.hpp>

#include "ShaderProgram.h"

class Renderable {
	public:
		virtual void render(glm::mat4 mvp) = 0;
		ShaderProgram* shaderProgram;
};

#endif