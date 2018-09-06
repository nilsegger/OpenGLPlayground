#include "Window.hpp"


Window::Window(short int width, short int height, const char * title)
	:width(width), height(height), title(title), window(nullptr)
{
	
	// Initialise GLFW
	//glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
	}

	if (!open()) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
	}
	setInputMode(GLFW_STICKY_KEYS, GL_TRUE);

	//glfwMakeContextCurrent(window->getWindow()); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
}


Window::~Window()
{
	//delete window;
}

bool Window::open(bool setCurrent)
{
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	return window != NULL;
}

bool Window::isOpen() const
{
	return glfwWindowShouldClose(window) == 0;
}

void Window::close()
{
	glfwTerminate();
}

void Window::clear(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
	
}

void Window::setInputMode(int mode, int value)
{
	glfwSetInputMode(window, mode, value);
}

GLFWwindow * Window::getWindow() const
{
	return window;
}
