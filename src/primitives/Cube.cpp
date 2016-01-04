#include "primitives/Cube.h"

Cube::Cube(ShaderProgram* s, Texture* t) : Primitive(s, t) {
	constructPrimitive();
	Primitive::create();
}

void Cube::constructPrimitive() {
	using namespace glm;
	vec3 vertexArray[] = {
		vec3(-0.5f, 0.0f, 0.5f),   vec3(0.5f, 0.0f, 0.5f),   vec3(0.5f, 1.0f, 0.5f),  vec3(-0.5f, 1.0f, 0.5f),
		vec3(-0.5f, 1.0f, -0.5f),  vec3(0.5f, 1.0f, -0.5f),  vec3(0.5f, 0.0f, -0.5f), vec3(-0.5f, 0.0f, -0.5f),
		vec3(0.5f, 0.0f, 0.5f),   vec3(0.5f, 0.0f, -0.5f),  vec3(0.5f, 1.0f, -0.5f),  vec3(0.5f, 1.0f, 0.5f),
		vec3(-0.5f, 0.0f, -0.5f),  vec3(-0.5f, 0.0f, 0.5f),  vec3(-0.5f, 1.0f, 0.5f), vec3(-0.5f, 1.0f, -0.5f)
	};
	/*unsigned int indexArray[] = {
		0,1,2,3, 4,5,6,7, 3,2,5,4,
		7,6,1,0, 8,9,10,11, 12,13,14,15
	};*/
	unsigned int indexArray[] = {
		0,1,2, 0,2,3,
		4,5,6, 4,6,7,
		3,2,5, 3,5,4,
		7,6,1, 7,1,0,
		8,9,10, 8,10,11,
		12,13,14, 12,14,15
	};
	vec2 uvArray[] = {
		vec2(0.0,0.0), vec2(1.0,0.0), vec2(1.0,1.0), vec2(0.0,1.0),
		vec2(0.0,0.0), vec2(1.0,0.0), vec2(1.0,1.0), vec2(0.0,1.0),
		vec2(0.0,0.0), vec2(1.0,0.0), vec2(1.0,1.0), vec2(0.0,1.0),
		vec2(0.0,0.0), vec2(1.0,0.0), vec2(1.0,1.0), vec2(0.0,1.0)
	};
	this->vertices = std::vector<vec3>(vertexArray, vertexArray + sizeof(vertexArray) / sizeof(vertexArray[0]));
	this->indices = std::vector<unsigned int>(indexArray, indexArray + sizeof(indexArray) / sizeof(indexArray[0]));
	this->uvs = std::vector<vec2>(uvArray, uvArray + sizeof(uvArray) / sizeof(uvArray[0]));

	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void Cube::render(glm::mat4 mvp) {
	Primitive::render(mvp);
}