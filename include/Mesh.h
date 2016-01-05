#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>

#include "Geometry.h"
#include "ShaderProgram.h"
#include "Texture.h"

using namespace std;

class Mesh : public Geometry {
	public:
		Mesh(ShaderProgram* shaderProgram, vector<glm::vec3> vertices, vector<glm::vec3> normals, vector<glm::vec2> uvs, vector<unsigned int> indices);
		void render(glm::mat4 mvp);
	private:
		void createMesh();
};

#endif