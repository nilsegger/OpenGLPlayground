#include "VertexArrayObject.hpp"

VertexArrayObject::VertexArrayObject(VertexBufferObject * vertexBufferObject)
	:vbo(vertexBufferObject)
{
	if (vertexBufferObject == nullptr) vbo = new VertexBufferObject();
	glGenVertexArrays(1, &bufferId);	
}

VertexArrayObject::VertexArrayObject(VertexBufferObject * vertexBufferObject, ElementBufferObject * elementBufferObject)
	:vbo(vertexBufferObject), ebo(elementBufferObject)
{
	if (vertexBufferObject == nullptr) vbo = new VertexBufferObject();
	if (elementBufferObject == nullptr) ebo = new ElementBufferObject();
	glGenVertexArrays(1, &bufferId);
}


VertexArrayObject::~VertexArrayObject()
{
	delete vbo;
	glDeleteVertexArrays(1, &bufferId);
}

void VertexArrayObject::setIndices(unsigned int * indices, unsigned short length, GLenum type)
{
	glBindVertexArray(bufferId);
	ebo->setIndices(indices, length);
}

void VertexArrayObject::setVertices(float * vertices, unsigned int length, unsigned short stride, GLenum type)
{
	glBindVertexArray(bufferId);
	vbo->setVertices(vertices, length, stride, type);
}

void VertexArrayObject::setVerColTex(float * vertices, unsigned int length, GLenum type)
{
	glBindVertexArray(bufferId);
	vbo->setVerColTex(vertices, length, type);
}

void VertexArrayObject::draw(unsigned int shaderProgram)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(bufferId);
	if(ebo == nullptr)	glDrawArrays(GL_TRIANGLES, 0, 3);
	else glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void VertexArrayObject::draw(unsigned int shaderProgram, unsigned int texture)
{
	glUseProgram(shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(bufferId);
	if (ebo == nullptr)	glDrawArrays(GL_TRIANGLES, 0, 3);
	else glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
