#include "PerspectiveCamera.hpp"


PerspectiveCamera::PerspectiveCamera(float width, float height, glm::vec3 position, glm::vec3 forward, glm::vec3 up)
	:Camera(width,height, position, forward, up)
{
	setFOV();
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::setFOV(float FOV)
{
	m_fov = FOV;
	setProjection();
}

float PerspectiveCamera::getFOV() const
{
	return m_fov;
}

void PerspectiveCamera::setProjection()
{
	m_projection = glm::perspective(glm::radians(m_fov), m_width / m_height, 0.01f, 100.0f);
}
