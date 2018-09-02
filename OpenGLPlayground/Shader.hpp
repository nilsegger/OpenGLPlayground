#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>

class Shader
{
public:
	Shader() = delete;
	Shader(GLenum type, char * path);
	~Shader();

	bool load();

	bool create();

	unsigned int get() const;
private:
	unsigned int id;
	GLenum type;
	char * path;
	char * shader;
};

