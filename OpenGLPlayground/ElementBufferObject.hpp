#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

class ElementBufferObject
{
public:
	ElementBufferObject();
	~ElementBufferObject();

	void setIndices(unsigned int * indices, unsigned short length, GLenum type = GL_STATIC_DRAW);
private:
	unsigned int bufferId;
};

