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
#include "Camera.h"
#include "Drawable.hpp"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H  

#define PLAYGROUNDPATH "C:/Users/NILSEGGE/OpenGLRoot/OpenGLRoot/OpenGLPlayground/OpenGLPlayground"
//#define PLAYGROUNDPATH "C:\\Users\\Nils\\Documents\\Projects\\playground\\OpenGLPlayground"

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

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	FT_Face face;
	if (FT_New_Face(ft, "C:\\Users\\NILSEGGE\\OpenGLRoot\\OpenGLRoot\\OpenGLPlayground\\OpenGLPlayground\\Actor-Regular.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;


	Window window(1024, 768, "MobileBrawl");

	Drawable::initDefShaders();

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	
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


	std::vector<unsigned int> indicesData;
	for (int i = 0; i < 6; i++) {
		indicesData.push_back(indices[i]);
	}

	Texture texture(PLAYGROUNDPATH"/container.jpg");
	texture.load();
	texture.create();

	//Drawable drawable(verticesData, &texture, nullptr);
	Drawable drawable(verticesData, nullptr, nullptr);

	glm::vec3 cubePositions[] = {
		//glm::vec3(0.0f,  0.0f,  0.0f),
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
	
	
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	Camera camera(1024.f, 768.f);

	double old = glfwGetTime();
	double deltaTime = 0.;

	do {
		window.clear();

		//printf("%f\n", deltaTime);

		for (unsigned int i = 0; i < 9; i++) {


			float cameraSpeed = float(5.0 * deltaTime); // adjust accordingly
			if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
				camera.move(cameraSpeed * cameraFront);
				//cameraPos += cameraSpeed * cameraFront;
			if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
				camera.move(-cameraSpeed * cameraFront);
				//cameraPos -= cameraSpeed * cameraFront;
			if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
				camera.move(-glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
				//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
				camera.move(glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
				//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.f*(i+1)), glm::vec3(0.5f, 1.0f, 0.0f));
			

			float radius = 10.0f;
			float camX = float(sin(glfwGetTime())) * radius;
			float camZ = float(cos(glfwGetTime())) * radius;
			glm::mat4 view;
			view = view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
			//glm::mat4 view = camera.getView();

			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(45.0f), 1024.f / 768.f, 0.1f, 100.0f);

			//drawable.draw(model, camera.getView(), camera.getProjection());

			drawable.draw(cubePositions[i], &camera);

			deltaTime = glfwGetTime() - old;
			old = glfwGetTime();
		}

		window.pollEvents();
		window.swapBuffers();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && window.isOpen());


}