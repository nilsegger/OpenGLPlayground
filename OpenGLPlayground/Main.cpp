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
#include "WorldBodyBuilder.hpp"
#include <Box2D\Box2D.h>

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

	//Drawable drawable(verticesData, &texture, nullptr);
	Drawable drawable(verticesData, nullptr, nullptr);

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
	
	
	PerspectiveCamera perspectiveCam(float(SCREEN_WIDTH), float(SCREEN_HEIGHT), glm::vec3(0.4f,0.4f,1.f));
	OrthographicCamera orthographicCam(float(SCREEN_WIDTH), float(SCREEN_HEIGHT));

	double old = glfwGetTime();
	double deltaTime = 0.;

	ShaderProgram textShader;
	textShader.attachShader(GL_VERTEX_SHADER, PATH"\\textShader.vertex");
	textShader.attachShader(GL_FRAGMENT_SHADER, PATH"\\textShader.fragment");
	textShader.create();


	Text fpsDisplay("FPS", PATH"/font.bmp", 25, glm::vec3(0.f,float(SCREEN_HEIGHT - 25), 0.f), &orthographicCam);
	Text cameraPositions("Camera Position: ", PATH"/font.bmp", 25, glm::vec3(0.f, float(SCREEN_HEIGHT - 50), 0.f), &orthographicCam);

	FPSCounter fpsCounter;

	b2World world(b2Vec2(0.f, -10.f));

	b2BodyDef groundBodyDef = WorldBodyBuilder::createBodyDef(b2_staticBody, b2Vec2(0.f, -10.f));
	b2Body* groundBody = WorldBodyBuilder::instantiateBody(groundBodyDef, &world);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);


	// 100 x 20

	float height = 20.f, width = 100.f;


	std::vector<float> groundBodyVerticesvec;

	float groundBodyVertices[] = {
		0.f, 0.f, 0.f, 0.f, 0.f,
		0.f, 1.f / SCREEN_HEIGHT * (WORLD_TO_PIXEL * height), 0.f, 0.f,0.f,
		1.f / SCREEN_WIDTH * (WORLD_TO_PIXEL * width), 0.f, 0.f, 0.f,0.f,

		0.f, 1.f / SCREEN_HEIGHT * (WORLD_TO_PIXEL * height), 0.f, 0.f,0.f,
		1.f / SCREEN_WIDTH * (WORLD_TO_PIXEL * width), 1.f / SCREEN_HEIGHT * (WORLD_TO_PIXEL * height), 0.f, 0.f, 0.f,
		1.f / SCREEN_WIDTH * (WORLD_TO_PIXEL * width), 0.f, 0.f, 0.f,0.f
	};

	for (int i = 0; i < 6 * 5; i++) {
		groundBodyVerticesvec.push_back(groundBodyVertices[i]);
	}

	Drawable groundBodyDrawable(groundBodyVerticesvec, nullptr, nullptr);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 10.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	std::vector<float> dynamicBodyVertices;
	float dynHeight = 2.f, dynWidth = 2.f;
	float dynamicVertices[] = {
		0.f, 0.f, 0.f, 0.f, 0.f,
		0.f, 1.f / SCREEN_HEIGHT * (WORLD_TO_PIXEL * dynHeight), 0.f, 0.f,0.f,
		1.f / SCREEN_WIDTH * (WORLD_TO_PIXEL * dynWidth), 0.f, 0.f, 0.f,0.f,

		0.f, 1.f / SCREEN_HEIGHT * (WORLD_TO_PIXEL * dynHeight), 0.f, 0.f,0.f,
		1.f / SCREEN_WIDTH * (WORLD_TO_PIXEL * dynWidth), 1.f / SCREEN_HEIGHT * (WORLD_TO_PIXEL * dynHeight), 0.f, 0.f, 0.f,
		1.f / SCREEN_WIDTH * (WORLD_TO_PIXEL * dynWidth), 0.f, 0.f, 0.f,0.f
	};

	for (int i = 0; i < 6 * 5; i++) {
		dynamicBodyVertices.push_back(dynamicVertices[i]);
	}

	Drawable dynamicBodyDrawable(dynamicBodyVertices, nullptr, nullptr);

	//float height = 2.f, width = 2.f;


	/*std::vector<float> groundBodyVerticesvec;

	float groundBodyVertices[] = {
		0.f, 0.f, 0.f, 0.f, 0.f,
		0.f, 1.f / SCREEN_HEIGHT * (WORLD_TO_PIXEL * height), 0.f, 0.f,0.f,
		1.f / SCREEN_WIDTH * (WORLD_TO_PIXEL * width), 0.f, 0.f, 0.f,0.f,

		0.f, 1.f / SCREEN_HEIGHT * (WORLD_TO_PIXEL * height), 0.f, 0.f,0.f,
		1.f / SCREEN_WIDTH * (WORLD_TO_PIXEL * width), 1.f / SCREEN_HEIGHT * (WORLD_TO_PIXEL * height), 0.f, 0.f, 0.f,
		1.f / SCREEN_WIDTH * (WORLD_TO_PIXEL * width), 0.f, 0.f, 0.f,0.f
	};

	for (int i = 0; i < 6 * 5; i++) {
		groundBodyVerticesvec.push_back(groundBodyVertices[i]);
	}*/


	



	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	do {
		std::cout << groundBody->GetPosition().y << " // " << body->GetPosition().y << std::endl;
		getchar();
		//getchar();
		world.Step(timeStep, velocityIterations, positionIterations);

		fpsDisplay.setText("FPS " + std::to_string(fpsCounter.getFPS()));
		cameraPositions.setText(std::to_string(int(perspectiveCam.getPosition().x * SCREEN_WIDTH)) + "/" + std::to_string(int(perspectiveCam.getPosition().y * SCREEN_HEIGHT)) + "/" + std::to_string(int(perspectiveCam.getPosition().z * SCREEN_WIDTH)));

		float cameraSpeed = float(.5 * deltaTime); // adjust accordingly
		if (glfwGetKey(window.getWindow(), GLFW_KEY_Q) == GLFW_PRESS)
			perspectiveCam.move(cameraSpeed * perspectiveCam.getForward());
		if (glfwGetKey(window.getWindow(), GLFW_KEY_E) == GLFW_PRESS)
			perspectiveCam.move(-cameraSpeed * perspectiveCam.getForward());
		if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
			perspectiveCam.move(-glm::normalize(glm::cross(perspectiveCam.getForward(), perspectiveCam.getUp())) * cameraSpeed);
		if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
			perspectiveCam.move(glm::normalize(glm::cross(perspectiveCam.getForward(), perspectiveCam.getUp())) * cameraSpeed);
		if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
			perspectiveCam.move(cameraSpeed * perspectiveCam.getUp());
		if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
			perspectiveCam.move(-cameraSpeed * perspectiveCam.getUp());

		window.clear(0.3f,0.3f,0.3f);

		groundBodyDrawable.draw(glm::vec3(0.f, (1.f / SCREEN_HEIGHT * (groundBody->GetPosition().y * WORLD_TO_PIXEL)) - (1.f / SCREEN_HEIGHT * (height / 2.f * WORLD_TO_PIXEL)) /*1.f - (1.f / SCREEN_HEIGHT * (height * WORLD_TO_PIXEL)) -.9f */,0.f), &perspectiveCam);
		dynamicBodyDrawable.draw(glm::vec3((body->GetPosition().x * WORLD_TO_PIXEL), (1.f / SCREEN_HEIGHT * (body->GetPosition().y * WORLD_TO_PIXEL)) - (1.f / SCREEN_HEIGHT * (dynHeight / 2.f * WORLD_TO_PIXEL)) /*1.f - (1.f / SCREEN_HEIGHT * (height * WORLD_TO_PIXEL)) -.9f */, 0.f), &perspectiveCam);
		/*for (int i = 0; i < 9; i++) {
			drawable.draw(cubePositions[i], &perspectiveCam);
		}*/
		

		cameraPositions.draw();
		fpsDisplay.draw();

		window.pollEvents();
		window.swapBuffers();

		deltaTime = glfwGetTime() - old;
		old = glfwGetTime();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && window.isOpen());


}