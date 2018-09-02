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
	bool isOpen() const;
	void close();

	void clear(GLclampf red = 0.f, GLclampf green = 0.f, GLclampf blue = 0.f, GLclampf alpha = 0.f);
	void pollEvents();
	void swapBuffers();

	void setInputMode(int mode = GLFW_STICKY_KEYS, int value = GL_TRUE);

	GLFWwindow * getWindow() const; //Should be removed
private:
	GLFWwindow * window;

	short int width;
	short int height;
	const char * title;

};

