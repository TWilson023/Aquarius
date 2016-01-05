#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/glm.hpp>
#include <vector>

#include "Renderable.h"
#include "ShaderProgram.h"
#include "Texture.h"

class Geometry : public Renderable {
	public:
		Geometry(ShaderProgram* shaderProgram, Texture* texture = NULL);
		void render(glm::mat4 mvp);
		void create();
		ShaderProgram* shaderProgram;
		Texture* texture;
		glm::vec3 color;
	protected:
		std::vector<glm::vec3> vertices, normals;
		std::vector<glm::vec2> uvs;
		std::vector<unsigned int> indices;
		GLuint vertexBuffer, uvBuffer, normalBuffer, elementBuffer;
		GLenum drawMode;
	private:
		GLuint textureID, colorID, hasTextureID;
};

#endif