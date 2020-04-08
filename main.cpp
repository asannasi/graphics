/* 
 * This program uses openGL and C++ to render graphics.
 * It's written to reinforce personal self-studying.
 */

#include "main.h"

int main(char* args) {
	int windowWidth = 640;
	int windowHeight = 480;
	char* windowTitle = "Graphics Project";

	// Initialize GLFW, which is a utility library for openGL
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return EXIT_FAILURE;
	}

	// Create GLFW window, which encapsulates a window and openGL context
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);//glfwGetPrimaryMonitor(), NULL);
	if (!window) {
		std::cerr << "Failed to initialize GLFW window" << std::endl;
		return EXIT_FAILURE;
	}

	// Make the openGL context for the created window the current one
	// A context stores openGL's state and is thread-local
	glfwMakeContextCurrent(window);

	// Initialize GLEW, which is a library that checks supported openGL extensions
	// at runtime on the target platform.
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate(); // free GLFW window before exiting
		return EXIT_FAILURE;
	}

	// Tell openGL window dimensions (can be different from glfw's)
	glViewport(0, 0, windowWidth, windowHeight);

	// Keep running until the window is told to close
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window); // swap front and back buffers for no flicker
		glfwPollEvents(); // check if any events are triggered
	}

	// Free resources
	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}