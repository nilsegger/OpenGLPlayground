#include "Text.hpp"

ShaderProgram * Text::s_shader = nullptr;

Text::Text()
{

	int width, height, nrChannels;

	unsigned char * data = stbi_load(PATH"/font.bmp", &width, &height, &nrChannels, 0);

	if (!data) {
		printf("Failed to load Texture %s\n", PATH"/font.bmp");
	}

}


Text::~Text()
{
}

void Text::draw()
{

}

void Text::initDefShader()
{
	s_shader = new ShaderProgram;
	s_shader->attachShader(GL_VERTEX_SHADER, PATH"/textShader.vertex");
	s_shader->attachShader(GL_FRAGMENT_SHADER ,PATH"/textShader.fragment");
	s_shader->create();
}
