// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "VertexBufferObject.hpp"
#include "VertexArrayObject.hpp"
int main() {

	// Initialise GLFW
	//glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	Window * window = new Window(1024, 768, "Tutorial 01");
	
	if (!window->open()) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	window->setInputMode(GLFW_STICKY_KEYS, GL_TRUE);

	//glfwMakeContextCurrent(window->getWindow()); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}


	

	char * vertexShaderSource = "#version 330 core\n layout(location = 0) in vec3 aPos; void main() {	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); }";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED %i \n", infoLog);
	}

	char * fragmentShaderSource = "#version 330 core\n out vec4 FragColor; void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);} ";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED %i \n", infoLog);
	}
	
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Error linking shaders to program.");
	}

	//glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	float vao_vertices[] = {
		-0.5f, -0.5f, 0.f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};


	std::vector<float> vec_vertices(12);



	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	for (int i = 0; i < 12; i++) {
		vec_vertices[i] = vertices[i];
	}

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};



	VertexArrayObject * vertexArrayObject = new VertexArrayObject(nullptr,nullptr);
	vertexArrayObject->setVertices(&vec_vertices[0], 12);
	vertexArrayObject->setIndices(indices, 6);

	

	do {
		window->clear(GL_COLOR_BUFFER_BIT);
		
		vertexArrayObject->draw(shaderProgram);

		window->pollEvents();
		window->swapBuffers();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && window->isOpen());

}