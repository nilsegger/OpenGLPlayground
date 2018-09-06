#include "Drawable.hpp"

Drawable::Drawable(std::vector<float> verticesData, ShaderProgram * shaderProgram, Texture * texture)
	:shaderProgram(shaderProgram), texture(texture)
{

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesData.size() * sizeof(float), &verticesData[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	verticesCount = unsigned int(verticesData.size() / 5*3);

}

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

void Drawable::draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	glBindTexture(GL_TEXTURE_2D, texture->get());

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->get(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->get(), "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->get(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glUseProgram(shaderProgram->get());
	glBindVertexArray(vao);
	if(ebo) glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);
	else glDrawArrays(GL_TRIANGLES, 0, verticesCount);

	
	
	
	
	

}

Drawable::~Drawable()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	if(ebo) glDeleteBuffers(1, &ebo);
}
