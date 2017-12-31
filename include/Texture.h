#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#define FOURCC_DXT1 0x31545844
#define FOURCC_DXT3 0x33545844
#define FOURCC_DXT5 0x35545844

class Texture {
	public:
		GLuint loadDDS(const char* path);
		GLuint loadBMP(const char* path);
		GLuint textureID;
};

#endif