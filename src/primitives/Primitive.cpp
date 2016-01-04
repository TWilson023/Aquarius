#include "primitives/Primitive.h"

Primitive::Primitive(ShaderProgram* s, Texture* t) : Geometry(s, t) {
	
}

void Primitive::render(glm::mat4 mvp) {
	Geometry::render(mvp);
}