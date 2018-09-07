#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

#include "ShaderProgram.hpp"

#include "config.hpp"

#include "stb_image.hpp"

class Text
{
public:
	Text();
	~Text();

	//void setPosition(glm::vec3 position);
	void draw();

private:

private:
	static ShaderProgram * s_shader;
public:
	static void initDefShader();
};

