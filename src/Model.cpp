#include "Model.h"

#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

Model::Model(const char* path, ShaderProgram* s, Texture* t) {
	GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	color = glm::vec3(1.0f, 1.0f, 1.0f);

	this->shaderProgram = s;

	this->texture = t;
	if(t != NULL)
		textureID = glGetUniformLocation(shaderProgram->programID, "textureSampler");

	loadOBJ(path);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}

void Model::render(glm::mat4 mvp) {
	shaderProgram->use();
	shaderProgram->mvp(mvp);

	if(this->texture != NULL) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->textureID);
		glUniform1i(textureID, 0);
	}

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

bool Model::loadOBJ(const char* path) {
	printf("Loading OBJ: %s\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tempVertices, tempNormals;
	std::vector<glm::vec2> tempUvs;

	FILE* file = fopen(path, "r");
	if(file == NULL) {
		printf("Failed to load OBJ file: %s\n", path);
		return false;
	}

	while (true) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if(res == EOF) {
			printf("OBJ file loaded!\n");
			break;
		}

		if(strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
		} else if(strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y;
			tempUvs.push_back(uv);
		} else if(strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		} else if(strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if(matches != 9) {
				printf("Failed to read OBJ: %s\n", path);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		} else {
			char uselessBuffer[1000];
			fgets(uselessBuffer, 1000, file);
		}
	}

	for(unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = tempVertices[vertexIndex - 1];
		glm::vec2 uv = tempUvs[uvIndex - 1];
		glm::vec3 normal = tempNormals[normalIndex - 1];

		this->vertices.push_back(vertex);
		this->uvs.push_back(uv);
		this->normals.push_back(normal);
	}

	return true;
}