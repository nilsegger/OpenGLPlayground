#pragma once
#include "Camera.hpp"
class OrthographicCamera :
	public Camera
{
public:
	OrthographicCamera() = delete;
	OrthographicCamera(float width, float height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	~OrthographicCamera();
private:
	void setProjection() override;
};

