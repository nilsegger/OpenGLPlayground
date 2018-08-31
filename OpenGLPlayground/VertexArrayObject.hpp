#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "VertexBufferObject.hpp"
#include "ElementBufferObject.hpp"

class VertexArrayObject
{
public:
	VertexArrayObject(VertexBufferObject * vertexBufferObject); //Nullptr allowed
	VertexArrayObject(VertexBufferObject * vertexBufferObject, ElementBufferObject * elementBufferObject); //Nullptr allowed
	VertexArrayObject() = delete;
	~VertexArrayObject();

	void setIndices(unsigned int * indices, unsigned short length, GLenum type = GL_STATIC_DRAW);
	void setVertices(float * vertices, unsigned int length, unsigned short stride = 3, GLenum type = GL_STATIC_DRAW);

	void draw(unsigned int shaderProgram);
private:
	unsigned int bufferId;
	VertexBufferObject * vbo;
	ElementBufferObject * ebo;
};

