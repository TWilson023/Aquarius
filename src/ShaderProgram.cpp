#include "ShaderProgram.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) {
	addShader(vertexFile, GL_VERTEX_SHADER);
	addShader(fragmentFile, GL_FRAGMENT_SHADER);
	load();
}

void ShaderProgram::use() {
	glUseProgram(programID);
	for(unsigned int i = 0; i < uniforms.size(); i++) {
		switch(uniforms[i].type) {
			case FLOAT:
				glUniform1f(uniforms[i].id, uniforms[i].value.vf[0]);
				break;
			case INT:
				glUniform1i(uniforms[i].id, uniforms[i].value.vi[0]);
				break;
		}
	}
	glUniform1f(glfwTimeID, (float) glfwGetTime());
}

void ShaderProgram::mvp(glm::mat4 mvp) {
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
}

GLuint ShaderProgram::setUniform(UniformType type, const char* name, UniformValue value) {
	for(unsigned int i = 0; i < uniforms.size(); i++) {
		if(strcmp(uniforms[i].name, name) == 0) {
			uniforms[i].value = value;
			return uniforms[i].id;
		}
	}
	ShaderUniform u;
	u.id = glGetUniformLocation(programID, name);
	u.type = type;
	u.name = name;
	u.value = value;
	uniforms.push_back(u);
	return u.id;
}

GLuint ShaderProgram::setUniformi(const char* name, int value) {
	UniformValue uv;
	uv.vi[0] = value;
	return ShaderProgram::setUniform(INT, name, uv);
}

GLuint ShaderProgram::setUniformf(const char* name, float value) {
	UniformValue uv;
	uv.vf[0] = value;
	return ShaderProgram::setUniform(FLOAT, name, uv);
}

std::string ShaderProgram::readFile(const char* file) {
	printf("Reading shader: %s\n", file);
	std::string sourceFile;
	std::ifstream stream(file, std::ios::in);
	if(stream.is_open()) {
		std::string line = "";
		while (getline(stream, line))
			sourceFile += line + "\n";
		stream.close();
	} else {
		printf("Failed to read shader: %s!\n", file);
		return NULL;
	}
	return sourceFile;
}

void ShaderProgram::addShader(const char* file, GLenum type) {
	Shader shader;
	shader.name = file;
	shader.type = type;
	shader.source = readFile(file);
	shaders.push_back(shader);
}

GLuint ShaderProgram::load() {
	programID = glCreateProgram();
	std::vector<GLuint> ids;
	for(unsigned int i = 0; i < shaders.size(); i++) {
		GLuint id = compileShader(shaders[i].source, shaders[i].type, shaders[i].name);
		glAttachShader(programID, id);
		ids.push_back(id);
	}
	glLinkProgram(programID);

	int infoLogLength;
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0) {
		std::vector<char> programError(infoLogLength + 1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programError[0]);
		printf("%s\n", &programError[0]);
	}

	for(unsigned int i = 0; i < ids.size(); i++) {
		glDetachShader(programID, ids[i]);
		glDeleteShader(ids[i]);
	}

	mvpID = glGetUniformLocation(programID, "MVP");
	glfwTimeID = glGetUniformLocation(programID, "glfwTime");

	return programID;
}

GLuint ShaderProgram::compileShader(std::string source, GLenum shaderType, const char* name) {
	GLuint shaderID = glCreateShader(shaderType);

	printf("Compiling shader: %s\n", name);
	const char* sourcePointer = source.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	int infoLogLength;

	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0) {
		std::vector<char> error(infoLogLength + 1);
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, &error[0]);
		printf("%s\n", &error[0]);
	}

	return shaderID;
}