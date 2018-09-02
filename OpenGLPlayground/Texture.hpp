#pragma once


#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "stb_image.hpp"
#include <stdio.h>
class Texture
{
public:
	Texture() = delete;
	Texture(char * path);
	~Texture();


	bool load();
	bool create();
	int getHeight() const;
	int getWidth() const;
	int getChannels() const;
	unsigned int get();

private:
	unsigned int id;
	char * path;
	unsigned char * data;
	int width;
	int height;
	int nrChannels;
};

