#include "ElementBufferObject.hpp"



ElementBufferObject::ElementBufferObject()
{
	glGenBuffers(1, &bufferId);
}


ElementBufferObject::~ElementBufferObject()
{
}

void ElementBufferObject::setIndices(unsigned int * indices, unsigned short length, GLenum type)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * length, indices, type);
}
