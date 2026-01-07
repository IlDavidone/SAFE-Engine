#ifndef TEXTURE_H
#define TEXTURE_H

#include "Includes.h"

enum TextureFilter {
	NEAREST,
	LINEAR,
};

class Texture {
public:
	GLuint ID;

	Texture(const char* imagePath, TextureFilter filterType);
	Texture(std::vector<const char*> faces);

	void Bind();
};



#endif
