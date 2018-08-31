#include "VertexBufferObject.hpp"



VertexBufferObject::VertexBufferObject()
{
	glGenBuffers(1, &bufferId);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &bufferId);
}

void VertexBufferObject::setVertices(float * vertices, unsigned int length, unsigned short stride, GLenum type)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * length, vertices, type);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

unsigned int VertexBufferObject::getBufferId() const
{
	return bufferId;
}

/*void VertexBufferObject::draw(unsigned int shaderProgram)
{
glBindBuffer(GL_ARRAY_BUFFER, bufferId);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesLength, vertices, GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glUseProgram(shaderProgram);
glDrawArrays(GL_TRIANGLES, 0, 3);
}*/