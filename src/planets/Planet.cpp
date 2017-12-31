#include "planets/Planet.h"

#include <iostream>

Planet::Planet(int radius) : radius(radius), Geometry(new ShaderProgram("shaders/simple.vert", "shaders/simple.frag"))
{
	create();
}

void Planet::create()
{
	chunk = new Chunk(1, );
	
	GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	
	// Generate vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, voxelObject->vertexCount * sizeof(glm::vec3), &voxelObject->vertices[0], GL_DYNAMIC_DRAW);
	
	GLint size = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	std::cout << "Triangle Vertices: " << voxelObject->vertexCount << std::endl;
	std::cout << "Buffer Size: " << size << std::endl;
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, voxelObject->vertexCount * sizeof(glm::vec3), &voxelObject->normals[0], GL_DYNAMIC_DRAW);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
}

void Planet::render(glm::mat4 mvp)
{
	shaderProgram->use();
	shaderProgram->mvp(mvp);

	glUniform3fv(colorID, 1, glm::value_ptr(color));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glDrawArrays(drawMode, 0, voxelObject->vertexCount);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}