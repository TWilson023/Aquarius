#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>

#include "Geometry.h"
#include "ShaderProgram.h"
#include "Texture.h"

class Model : Geometry {
	public:
		Model(const char* path, ShaderProgram* s, Texture* t = NULL);
		bool loadOBJ(const char* path);
		void render(glm::mat4 mvp);
		glm::vec3 color;
		Texture* texture;
		ShaderProgram* shaderProgram;
	private:
		void init();
		GLuint vertexBuffer, uvBuffer;
		GLuint textureID, colorID;
		float time;
		std::vector<glm::vec3> vertices, normals;
		std::vector<glm::vec2> uvs;
};

#endif