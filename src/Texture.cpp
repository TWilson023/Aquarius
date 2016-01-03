#include "Texture.h"

GLuint Texture::loadBMP(const char* path) {
	printf("Loading BMP file: %s\n", path);
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;

	unsigned char* data;

	FILE* file = fopen(path, "rb");
	if (!file) {
		printf("Failed to open BMP file: %s\n", path);
		return 0;
	}

	const char* invalidMessage = "Invalid BMP file: %s\n";

	if (fread(header, 1, 54, file) != 54){ 
		printf(invalidMessage, path);
		return 0;
	}
	if (header[0] != 'B' || header[1] != 'M'){
		printf(invalidMessage, path);
		return 0;
	}
	if (*(int*)&(header[0x1E]) != 0) {
		printf(invalidMessage, path);
		return 0;
	}
	if (*(int*)&(header[0x1C]) != 24) {
		printf(invalidMessage, path);
		return 0;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0) imageSize=width*height*3;
	if (dataPos == 0) dataPos=54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	delete[] data;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);

	this->textureID = textureID;
	return textureID;
}

GLuint Texture::loadDDS(const char* path) {
	printf("Loading DDS file: %s\n", path);
	unsigned char header[124];

	FILE *fp; 

	fp = fopen(path, "rb"); 
	if (fp == NULL){
		printf("Failed to open DDS file: %s\n", path);
		return 0;
	}
   
	char filecode[4]; 
	fread(filecode, 1, 4, fp); 
	if (strncmp(filecode, "DDS ", 4) != 0) { 
		fclose(fp); 
		return 0; 
	}
	
	fread(&header, 124, 1, fp);

	unsigned int height = *(unsigned int*)&(header[8 ]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize	= *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);

	unsigned char * buffer;
	unsigned int bufSize;
	bufSize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
	buffer = (unsigned char*)malloc(bufSize * sizeof(unsigned char)); 
	fread(buffer, 1, bufSize, fp); 

	fclose(fp);

	unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4; 
	unsigned int format;
	switch(fourCC) 
	{ 
		case FOURCC_DXT1: 
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
			break; 
		case FOURCC_DXT3: 
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
			break; 
		case FOURCC_DXT5: 
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
			break; 
		default: 
			free(buffer); 
			return 0; 
	}

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);	
	
	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
	unsigned int offset = 0;

	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) 
	{ 
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,  
			0, size, buffer + offset); 
	 
		offset += size; 
		width  /= 2; 
		height /= 2; 

		if(width < 1) width = 1;
		if(height < 1) height = 1;

	}
	free(buffer); 

	printf("DDS file loaded!\n");
	this->textureID = textureID;
	return textureID;
}