#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <glm/glm.hpp>

#include "Geometry.h"
#include "ShaderProgram.h"
#include "Texture.h"

class Primitive : public Geometry {
	public:
		Primitive(ShaderProgram* s, Texture* t = NULL);
		void render(glm::mat4 mvp);
		virtual void constructPrimitive() {};
};

#endif