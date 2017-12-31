#include "Geometry.h"

#include <stdio.h>
#include <glm/gtc/type_ptr.hpp>

Geometry::Geometry(ShaderProgram* shaderProgram, Texture* texture) : Renderable() {
	this->drawMode = GL_TRIANGLES;
	this->shaderProgram = shaderProgram;
	this->texture = texture;
	if(this->texture != NULL)
		textureID = shaderProgram->createUniform("textureSampler");

	color = glm::vec3(1.0f, 1.0f, 1.0f);
	colorID = shaderProgram->createUniform("color");

	hasTextureID = shaderProgram->createUniform("hasTexture");
}

void Geometry::create() {
	GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}

void Geometry::render(glm::mat4 mvp) {
	shaderProgram->use();
	shaderProgram->mvp(mvp);

	if(this->texture != NULL) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->textureID);
		glUniform1i(textureID, 0);
		glUniform1i(hasTextureID, 1);
	} else {
		glUniform1i(hasTextureID, 0);
	}
	glUniform3fv(colorID, 1, glm::value_ptr(color));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	/*glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);*/ // TODO:  blah

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	if(indices.size() == 0)
		glDrawArrays(drawMode, 0, vertices.size());
	else {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glDrawElements(drawMode, indices.size(), GL_UNSIGNED_INT, (void*) 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
};