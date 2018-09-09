#include "FPSCounter.h"

FPSCounter::FPSCounter()
{
	m_timer_start = glfwGetTime();
}

short FPSCounter::getFPS()
{
	m_counter++;
	if (glfwGetTime() - m_timer_start > 1.0) {
		m_fps = m_counter;
		m_counter = 0;
		m_timer_start = glfwGetTime();
	}
	return m_fps;
}
