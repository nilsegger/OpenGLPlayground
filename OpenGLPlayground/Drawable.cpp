#include "Drawable.hpp"

ShaderProgram * Drawable::s_colorShader = nullptr;
ShaderProgram * Drawable::s_textureShader = nullptr;
Drawable::Drawable(std::vector<float> verticesData, Texture * texture, ShaderProgram * shaderProgram)
	:texture(texture), shaderProgram(shaderProgram)
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
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	verticesCount = unsigned int(verticesData.size() / 5*3);


	if (shaderProgram == nullptr) {
		if (texture == nullptr) this->shaderProgram = s_colorShader;
		else this->shaderProgram = s_textureShader;
	}

}

Drawable::Drawable(std::vector<float> verticesData, std::vector<unsigned int> indices, Texture * texture, ShaderProgram * shaderProgram)
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


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	verticesCount = unsigned int(indices.size());

	if (shaderProgram == nullptr) {
		if (texture == nullptr) this->shaderProgram = s_colorShader;
		else this->shaderProgram = s_textureShader;
	}
}

void Drawable::draw(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection)
{
	glBindTexture(GL_TEXTURE_2D, texture->get());

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->get(), "transformation"), 1, GL_FALSE, glm::value_ptr(glm::mat4(projection * view * model)));

	glUseProgram(shaderProgram->get());
	glBindVertexArray(vao);
	if(ebo) glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);
	else glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}

void Drawable::draw(glm::vec3 &position, Camera * camera)
{
	if(texture != nullptr) glBindTexture(GL_TEXTURE_2D, texture->get());
	glUseProgram(shaderProgram->get());
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->get(), "transformation"), 1, GL_FALSE, glm::value_ptr(glm::mat4(camera->getProjection() * camera->getView() * glm::translate(glm::mat4(1.f), position))));
	

	glBindVertexArray(vao);
	if (ebo) glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);
	else glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}

void Drawable::draw()
{
	
	glUseProgram(shaderProgram->get());

	if (texture != nullptr) glBindTexture(GL_TEXTURE_2D, texture->get());
	else glUniform4fv(glGetUniformLocation(shaderProgram->get(), "textureColor"), 1, glm::value_ptr(m_color));

	glm::mat4 translation = glm::translate(glm::mat4(1.f), m_position);
	translation = glm::rotate(translation, m_angle, glm::vec3(0.f, 0.f, 1.f));
	translation = glm::translate(translation, glm::vec3(-m_origin.x, -m_origin.y, 0.f));

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->get(), "transformation"), 1, GL_FALSE, glm::value_ptr(glm::mat4(m_camera->getProjection() * m_camera->getView() * translation)));


	glBindVertexArray(vao);
	if (ebo) glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);
	else glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}


void Drawable::setPosition(glm::vec3 position)
{
	m_position = position;
}

void Drawable::setAngle(float radian)
{
	m_angle = radian;
}

void Drawable::setCamera(Camera * camera)
{
	m_camera = camera;
}

void Drawable::setColor(glm::vec4 color)
{
	m_color = color;
}

void Drawable::setLocalOrigin(glm::vec3 origin)
{
	m_origin = origin;
}

Drawable::~Drawable()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	if(ebo) glDeleteBuffers(1, &ebo);
}

void Drawable::initDefShaders()
{
	s_colorShader = new ShaderProgram;
	s_colorShader->attachShader(GL_VERTEX_SHADER, PATH"\\colorShader.vertex");
	s_colorShader->attachShader(GL_FRAGMENT_SHADER, PATH"\\colorShader.fragment");
	s_colorShader->create();
	
	s_textureShader = new ShaderProgram;
	s_textureShader->attachShader(GL_VERTEX_SHADER, PATH"\\textureShader.vertex");
	s_textureShader->attachShader(GL_FRAGMENT_SHADER, PATH"\\textureShader.fragment");
	s_textureShader->create();
}
