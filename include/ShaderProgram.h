#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

struct Shader {
	const char* name;
	GLenum type;
	std::string source;
};

class ShaderProgram {
	public:
		ShaderProgram() {};
		ShaderProgram(const char* vertexFile, const char* fragmentFile);
		GLuint load();
		void addShader(const char* file, GLenum type);
		void use();
		void mvp(glm::mat4 mvp);
		GLuint createUniform(const char* name);
		GLuint programID;
	private:
		GLuint compileShader(std::string source, GLenum shaderType, const char* name);
		GLuint mvpID, glfwTimeID;
		std::string readFile(const char* file);
		std::vector<Shader> shaders;
};

#endif