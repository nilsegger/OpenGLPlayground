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
#include "Camera.hpp"

#define DEFAULT_TEXTURE_SHADER_PATH "C:\\Users\\NILSEGGE\\OpenGLRoot\\OpenGLRoot\\OpenGLPlayground\\OpenGLPlayground"


class Drawable
{
public:
	Drawable() = delete;
	Drawable(std::vector<float> verticesData, Texture * texture, ShaderProgram * shaderProgram);
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

public:
	static void initDefShaders();
private:
	static ShaderProgram * s_textureShader;
	static ShaderProgram * s_colorShader;
};

