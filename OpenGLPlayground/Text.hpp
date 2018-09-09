#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <map>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

#include "ShaderProgram.hpp"

#include "config.hpp"

#include "Font.hpp"

#include "Drawable.hpp"

struct Character {
	float m_offset;
	Drawable* m_drawable;
};

class Text
{
public:
	//Text(Font * font);
	Text(char * text, char * fontPath, float size, glm::vec3 position, Camera * camera);
	~Text();

	void setText(std::string text);
	void setText(char * text);
	void setPosition(glm::vec3 position);
	void draw();

private:
	float m_size;
	Camera * m_camera;
	Font * m_font;
	std::string m_old_text;
	glm::vec3 m_position;
	std::vector<Character*> m_characters;
	void clearCharacters();
private:
	static ShaderProgram * s_shader;
public:
	static void initDefShader();
};

