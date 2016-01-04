#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>

#include "Primitive.h"
#include "../ShaderProgram.h"
#include "../Texture.h"

class Cube : public Primitive {
	public:
		Cube(ShaderProgram* s, Texture* t = NULL);
		void render(glm::mat4 mvp);
		void constructPrimitive();
};

#endif