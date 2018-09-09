#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera
{
public:
	Camera() = delete;
	Camera(float width, float height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	~Camera();

	void move(glm::vec3 forward);
	void move(float x, float y, float z = 0);
	void setPosition(glm::vec3 position);

	glm::mat4 getView() const;
	glm::mat4 getProjection() const;

	glm::vec3 getForward() const;
	glm::vec3 getUp() const;
	glm::vec3 getPosition() const;
protected:
	virtual void setProjection() = 0;

	float m_width, m_height;

	glm::mat4 m_view;
	glm::mat4 m_projection;

	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
};

