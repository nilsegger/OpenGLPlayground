#include "Texture.hpp"


Texture::Texture(char * path)
	:path(path)
{
	glGenTextures(1, &id);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

bool Texture::load()
{

	data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (!data) {
		printf("Failed to load %s\n", data);
		return false;
	}
	return true;
}

bool Texture::create()
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	return true;
}

int Texture::getHeight() const
{
	return height;
}

int Texture::getWidth() const
{
	return width;
}

int Texture::getChannels() const
{
	return nrChannels;
}

unsigned int Texture::get()
{
	return id;
}
