#include "OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(float width, float height, glm::vec3 position, glm::vec3 forward, glm::vec3 up)
	:Camera(width,height,position,forward, up)
{
	setProjection();
}


OrthographicCamera::~OrthographicCamera()
{
}

void OrthographicCamera::setProjection()
{
	m_projection = glm::ortho(0.0f, m_width, 0.0f, m_height);
}
