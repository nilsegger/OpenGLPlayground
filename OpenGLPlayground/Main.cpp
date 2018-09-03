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

#include "stb_image.hpp"

#include "Window.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include "Drawable.hpp"

#define PLAYGROUNDPATH "C:/Users/NILSEGGE/OpenGLRoot/OpenGLRoot/OpenGLPlayground/OpenGLPlayground"

int main() {

	

	// Initialise GLFW
	//glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	Window window(1024, 768, "Tutorial 01");
	
	if (!window.open()) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	window.setInputMode(GLFW_STICKY_KEYS, GL_TRUE);

	//glfwMakeContextCurrent(window->getWindow()); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}


	Shader vertexShader(GL_VERTEX_SHADER, PLAYGROUNDPATH"/shader.vertex");
	vertexShader.load();
	vertexShader.create();
	Shader fragmentShader(GL_FRAGMENT_SHADER, PLAYGROUNDPATH"/shader.fragment");
	fragmentShader.load();
	fragmentShader.create();

	ShaderProgram shaderProgram;
	shaderProgram.attachShader(vertexShader.get());
	shaderProgram.attachShader(fragmentShader.get());
	shaderProgram.create();


	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	
	float vertices[] = {
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
	};

	std::vector<float> verticesData;

	for (int i = 0; i < 32; i++) {
		verticesData.push_back(vertices[i]);
	}


	std::vector<unsigned int> indicesData;
	for (int i = 0; i < 6; i++) {
		indicesData.push_back(indices[i]);
	}

	Texture texture(PLAYGROUNDPATH"/container.jpg");
	texture.load();
	texture.create();

	Drawable drawable(verticesData, indicesData, &shaderProgram, &texture);

	do {
		window.clear();

		drawable.draw();

		window.pollEvents();
		window.swapBuffers();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && window.isOpen());


}