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

#include "config.hpp"


class Drawable
{
public:
	Drawable() = delete;
	Drawable(std::vector<float> verticesData, Texture * texture, ShaderProgram * shaderProgram);
	Drawable(std::vector<float> verticesData, std::vector<unsigned int> indices, Texture * texture, ShaderProgram * shaderProgram);

	void draw(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection);
	void draw(glm::vec3 &position, Camera * camera);

	void draw(); //Use only when position etc is set

	void setPosition(glm::vec3 position);
	void setAngle(float radian);
	void setCamera(Camera * camera);

	~Drawable();
private:
	unsigned int vbo, ebo = 0, vao;
	unsigned int verticesCount;

private:
	ShaderProgram * shaderProgram;
	Texture * texture;

	glm::vec3 m_position;
	float m_angle; //radian
	Camera * m_camera = nullptr;


public:
	static void initDefShaders();
private:
	static ShaderProgram * s_textureShader;
	static ShaderProgram * s_colorShader;
};

