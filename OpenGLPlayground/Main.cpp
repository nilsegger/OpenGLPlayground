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
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
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


	Shader * vertexShader = new Shader(GL_VERTEX_SHADER, "C:/Users/Nils/Documents/Projects/playground/OpenGLPlayground/shader.vertex");
	vertexShader->load();
	vertexShader->create();
	Shader * fragmentShader = new Shader(GL_FRAGMENT_SHADER, "C:/Users/Nils/Documents/Projects/playground/OpenGLPlayground/shader.fragment");
	fragmentShader->load();
	fragmentShader->create();

	ShaderProgram * shaderProgram = new ShaderProgram();
	shaderProgram->attachShader(vertexShader->get());
	shaderProgram->attachShader(fragmentShader->get());
	shaderProgram->create();

	float vao_vertices[] = {
		-0.5f, -0.5f, 0.f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};


	std::vector<float> vec_vertices(12);

	/*float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};*/

	/*for (int i = 0; i < 12; i++) {
		vec_vertices[i] = vertices[i];
	}*/

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	/*VertexArrayObject * vertexArrayObject = new VertexArrayObject(nullptr,nullptr);
	vertexArrayObject->setVertices(&vec_vertices[0], 12);
	vertexArrayObject->setIndices(indices, 6);*/


	
	float vertices[] = {

		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
	};

	VertexArrayObject * vertexArrayObject = new VertexArrayObject(nullptr, nullptr);
	vertexArrayObject->setVerColTex(&vec_vertices[0], 32);
	vertexArrayObject->setIndices(indices, 6);

	Texture * texture = new Texture("C:/Users/Nils/Documents/Projects/playground/Debug/container.jpg");
	texture->load();
	texture->create();

	glUniform1i(glGetUniformLocation(shaderProgram->get(), "texture1"), 0);

	do {
		window->clear();
		
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram->get(), "ourColor");
		glUseProgram(shaderProgram->get());
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		vertexArrayObject->draw(shaderProgram->get());*/

		vertexArrayObject->draw(shaderProgram->get(), texture->get());

		window->pollEvents();
		window->swapBuffers();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && window->isOpen());

	delete shaderProgram;
	delete texture;
	delete vertexArrayObject;

}