#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <stdio.h>
#include "Shader.hpp"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void attachShader(GLenum type, char * path);
	void attachShader(unsigned int shader); //delete Shader if no other program is going to need it
	bool create();

	unsigned int get() const;

	bool setFloat(char * uniform, float value);
private:
	unsigned int id;
};

