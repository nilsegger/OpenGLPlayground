#pragma once
#include "Camera.hpp"
class PerspectiveCamera :
	public Camera
{
public:
	PerspectiveCamera() = delete;
	PerspectiveCamera(float width, float height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	~PerspectiveCamera();

	void setFOV(float FOV = 45.f);
	float getFOV() const;
private:
	void setProjection() override;
	float m_fov;
};

