#include "Mesh.h"

Mesh::Mesh(ShaderProgram* shaderProgram, vector<glm::vec3> vertices, vector<glm::vec3> normals, vector<glm::vec2> uvs, vector<unsigned int> indices) : Geometry(shaderProgram) {
	this->shaderProgram = shaderProgram;
	this->vertices = vertices;
	this->normals = normals;
	this->uvs = uvs;
	this->indices = indices;

	Geometry::create();
}

void Mesh::render(glm::mat4 mvp) {
	Geometry::render(mvp);
}