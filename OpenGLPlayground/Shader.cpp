#include "Shader.hpp"



Shader::Shader(GLenum type, char * path)
	:type(type), path(path)
{
}


Shader::~Shader()
{
	glDeleteShader(id);
}

bool Shader::load()
{
	std::ifstream file(path, std::ios::binary | std::ios::ate);

	if (file.fail()) {
		printf("Failed to open Shader %s", path);
		return false;
	}
	

	unsigned int size = file.tellg();

	if (size == 0) return false;

	shader = new char[size + 1];
	file.seekg(0);
	for (int i = 0; i < size; i++) {
		shader[i] = file.get();
	}
	shader[size] = 0;
	return true;
}

bool Shader::create()
{
	if (!shader) return false;

	id = glCreateShader(type);
	glShaderSource(id, 1, &shader, NULL);
	glCompileShader(id);

	int  success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		if(type == GL_VERTEX_SHADER) printf("Failed to create GL_VERTEX_SHADER\nInfo:%sFile:%s\n", infoLog, path);
		else  printf("Failed to create GL_FRAGMENT_SHADER\nInfo:%sFile:%s\n", infoLog, path);
		return false;
	}
	return true;
}

unsigned int Shader::get() const
{
	return id;
}
