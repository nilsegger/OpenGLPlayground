#include "ShaderProgram.hpp"



ShaderProgram::ShaderProgram()
{
	id = glCreateProgram();
}


ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
}

void ShaderProgram::attachShader(unsigned int shader)
{
	glAttachShader(id, shader);
}

bool ShaderProgram::create()
{

	glLinkProgram(id);

	GLint success;

	glGetProgramiv(id, GL_LINK_STATUS, &success);

	char infoLog[512];

	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		printf("Creating shader program failed.\n%s", infoLog);
		return false;
	}

	return true;
}

unsigned int ShaderProgram::get() const
{
	return id;
}

bool ShaderProgram::setFloat(char * uniform, float value)
{

	int uniformLocation = glGetUniformLocation(id, uniform);
	if (uniformLocation == -1) {
		printf("Failed to find %s", uniform);
		return false;
	}
	glUniform1f(uniformLocation, value);
	return true;
}
