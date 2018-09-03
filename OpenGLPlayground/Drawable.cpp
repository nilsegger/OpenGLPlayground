#include "Drawable.hpp"

Drawable::Drawable(std::vector<float> verticesData, std::vector<unsigned int> indices, ShaderProgram * shaderProgram, Texture * texture)
	:shaderProgram(shaderProgram), texture(texture)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesData.size() * sizeof(float), &verticesData[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesx), indicesx, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	verticesCount = unsigned int(indices.size());
}

void Drawable::draw()
{
	glBindTexture(GL_TEXTURE_2D, texture->get());
	glUseProgram(shaderProgram->get());
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);
}

Drawable::~Drawable()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}
