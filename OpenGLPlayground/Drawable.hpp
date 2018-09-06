#pragma once

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <vector>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Camera.h"
class Drawable
{
public:
	Drawable() = delete;
	Drawable(std::vector<float> verticesData, ShaderProgram * shaderProgram, Texture * texture);
	Drawable(std::vector<float> verticesData, std::vector<unsigned int> indices, ShaderProgram * shaderProgram, Texture * texture);

	void draw(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection);
	void draw(glm::vec3 &position, Camera * camera);

	~Drawable();
private:
	unsigned int vbo, ebo = 0, vao;
	unsigned int verticesCount;

private:
	ShaderProgram * shaderProgram;
	Texture * texture;
};

