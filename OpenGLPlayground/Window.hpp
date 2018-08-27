#pragma once

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>

#include <string>

class Window
{
public:
	Window() = delete;
	Window(short int width, short int height, const char * title);
	~Window();

	bool open(bool setCurrent = true);
	void close();

	GLFWwindow * getWindow() const;
private:
	GLFWwindow * window;

	short int width;
	short int height;
	const char * title;

};

