// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
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
#include "Camera.hpp"
#include "Drawable.hpp"
#include "PerspectiveCamera.hpp"
#include "OrthographicCamera.hpp"

#include "Text.hpp"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "FPSCounter.h"
#include "config.hpp"

/*

m for members
c for constants/readonlys
p for pointer (and pp for pointer to pointer)
v for volatile
s for static
i for indexes and iterators
e for events

*/



int main() {

	Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "MobileBrawl");

	Text::initDefShader();
	Drawable::initDefShaders();

	/*unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};*/

	
	/*float vertices[] = {
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
	};*/

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	std::vector<float> verticesData;

	for (int i = 0; i < sizeof(vertices) / sizeof(float); i++) {
		verticesData.push_back(vertices[i]);
	}


	/*std::vector<unsigned int> indicesData;
	for (int i = 0; i < 6; i++) {
		indicesData.push_back(indices[i]);
	}*/

	Texture texture(PATH"/container.jpg");
	texture.load();
	texture.create();

	Drawable drawable(verticesData, &texture, nullptr);
	//Drawable drawable(verticesData, nullptr, nullptr);

	glm::vec3 cubePositions[] = {
		glm::vec3(2.0f,  0.0f,  -100.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	
	
	PerspectiveCamera perspectiveCam(float(SCREEN_WIDTH), float(SCREEN_HEIGHT));
	OrthographicCamera orthographicCam(float(SCREEN_WIDTH), float(SCREEN_HEIGHT));

	double old = glfwGetTime();
	double deltaTime = 0.;

	ShaderProgram textShader;
	textShader.attachShader(GL_VERTEX_SHADER, PATH"\\textShader.vertex");
	textShader.attachShader(GL_FRAGMENT_SHADER, PATH"\\textShader.fragment");
	textShader.create();


	Text text("FPS", PATH"/font.bmp", 25, glm::vec3(0.f,float(SCREEN_HEIGHT - 25), 0.f), &orthographicCam);
	
	FPSCounter fpsCounter;

	do {
		text.setText("FPS " + std::to_string(fpsCounter.getFPS()));

		float cameraSpeed = float(1.0 * deltaTime); // adjust accordingly
		if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
			perspectiveCam.move(cameraSpeed * perspectiveCam.getForward());
		if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
			perspectiveCam.move(-cameraSpeed * perspectiveCam.getForward());
		if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
			perspectiveCam.move(-glm::normalize(glm::cross(perspectiveCam.getForward(), perspectiveCam.getUp())) * cameraSpeed);
		if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
			perspectiveCam.move(glm::normalize(glm::cross(perspectiveCam.getForward(), perspectiveCam.getUp())) * cameraSpeed);

		window.clear(0.3f,0.3f,0.3f);

		

		for (int i = 0; i < 9; i++) {
			drawable.draw(cubePositions[i], &perspectiveCam);
		}
		

		text.draw();

		window.pollEvents();
		window.swapBuffers();

		deltaTime = glfwGetTime() - old;
		old = glfwGetTime();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && window.isOpen());


}