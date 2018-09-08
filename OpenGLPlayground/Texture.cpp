#include "Texture.hpp"


Texture::Texture(char * path)
	:path(path)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

bool Texture::load(bool flipImage)
{
	stbi_set_flip_vertically_on_load(flipImage);
	data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (!data) {
		printf("Failed to load Texture %s\n", path);
		return false;
	}
	return true;
}

bool Texture::create()
{
	glBindTexture(GL_TEXTURE_2D, id);
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
