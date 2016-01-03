#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

enum UniformType {
	FLOAT,
	FLOAT2,
	FLOAT3,
	INT,
	INT2,
	INT3,
};

union UniformValue {
	float vf[3];
	int vi[3];
};

struct Shader {
	const char* name;
	GLenum type;
	std::string source;
};

struct ShaderUniform {
	GLuint id;
	UniformType type;
	const char* name;
	UniformValue value;
};

class ShaderProgram {
	public:
		ShaderProgram() {};
		ShaderProgram(const char* vertexFile, const char* fragmentFile);
		GLuint load();
		void addShader(const char* file, GLenum type);
		void use();
		void mvp(glm::mat4 mvp);
		GLuint setUniform(UniformType type, const char* name, UniformValue value);
		GLuint setUniformi(const char* name, int value);
		GLuint setUniformf(const char* name, float value);
		GLuint programID;
	private:
		GLuint compileShader(std::string source, GLenum shaderType, const char* name);
		GLuint mvpID, glfwTimeID;
		std::string readFile(const char* file);
		std::vector<Shader> shaders;
		std::vector<ShaderUniform> uniforms;
};

#endif