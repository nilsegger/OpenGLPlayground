#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

class FPSCounter
{
public:
	FPSCounter();
	short getFPS();
private:
	short m_counter = 0;
	double m_timer_start = 0.f;
	short m_fps = 0;
};

