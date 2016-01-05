#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>

#include "Geometry.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Mesh.h"

class Model : public Renderable {
	public:
		Model(const char* path, ShaderProgram* shaderProgram);
		ShaderProgram* shaderProgram;
		std::vector<Mesh> meshes;
		bool loadOBJ(const char* path);
		void render(glm::mat4 mvp);
	private:
		void init();
};

#endif