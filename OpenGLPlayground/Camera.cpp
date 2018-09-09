#include "Camera.hpp"


Camera::Camera(float width, float height,  glm::vec3 position, glm::vec3 forward, glm::vec3 up)
	:m_position(position), m_forward(forward), m_up(up), m_width(width), m_height(height)
{
	setPosition(position);
}

Camera::~Camera()
{
}

void Camera::move(glm::vec3 forward)
{
	move(forward.x, forward.y, forward.z);
}

void Camera::move(float x, float y, float z)
{
	m_position += glm::vec3(x, y, z);
	m_view = glm::lookAt(m_position, m_position + m_forward, m_up);
}

void Camera::setPosition(glm::vec3 position)
{
	m_position = position;
	m_view = glm::lookAt(m_position, m_position + m_forward, m_up);
}
/*
void Camera::setFOV(float fov)
{
	m_fov = fov;
	setProjection();
}
*/
glm::mat4 Camera::getView() const
{
	return m_view;
}

glm::mat4 Camera::getProjection() const
{
	return m_projection;
}

glm::vec3 Camera::getForward() const
{
	return m_forward;
}

glm::vec3 Camera::getUp() const
{
	return m_up;
}

glm::vec3 Camera::getPosition() const
{
	return m_position;
}
