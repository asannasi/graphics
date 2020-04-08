/* 
 * This program uses openGL and C++ to render graphics.
 * It's written to reinforce personal self-studying.
 */

#include "main.h"

#define MAJOR_VERSION 3
#define MINOR_VERSION 3
#define INFO_LOG_BUFFER_SIZE 512

namespace {
	// Set window properties
	int windowWidth = 800;
	int windowHeight = 600;
	const char* windowTitle = "Graphics Project";

	std::string vShaderFilename = "shader.vert";
	std::string fShaderFilename = "shader.frag";
	std::string objFilename = "a.obj";
};

inline void compileShader(GLuint& id, GLenum type, std::string filename) {
	// Get ref id for shader object
	id = glCreateShader(type);
	// Parse shader file and compile at runtime
	ShaderFile file = ShaderFile(filename);
	const char* code = file.getCode()->c_str();
	glShaderSource(id, 1, &code, NULL);
	glCompileShader(id);
	// If compilation failed, throw exception and print compile errors
	int compileSuccess;
	char infoLogBuffer[INFO_LOG_BUFFER_SIZE];
	glGetShaderiv(id, GL_COMPILE_STATUS, &compileSuccess);
	if (!compileSuccess) {
		glGetShaderInfoLog(id, INFO_LOG_BUFFER_SIZE, NULL, infoLogBuffer);
		std::cerr << infoLogBuffer << std::endl;
		throw std::exception("Shader not compiled. Check cerr.");
	}
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	// Tell openGL the window dimensions (can be different from glfw's)
	glViewport(0, 0, width, height);
}

int main(void) {

	// Make sure platform is not OSX
	#ifdef __APPLE__
	std::cerr << "Program supports Windows, not OSX." << std::endl;
	return EXIT_FAILURE;
	#endif

	// Initialize GLFW, which is a utility library for openGL
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return EXIT_FAILURE;
	}

	// Check openGL version to be 3.3 and only use core functions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW window, which encapsulates a window and openGL context
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, 
										  windowTitle, NULL, NULL);
	if (!window) {
		std::cerr << "Failed to initialize GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Make the openGL context for the created window the current one
	// A context stores openGL's state and is thread-local
	glfwMakeContextCurrent(window);

	// Set the callback function when the window is resized
	glfwSetFramebufferSizeCallback(window, windowResizeCallback);

	// Initialize GLEW, which is a library that checks supported openGL 
	// extensions at runtime on the target platform.
	glewExperimental = GL_TRUE;
	if (glewInit() || !glGenVertexArrays) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate(); // free GLFW window before exiting
		return EXIT_FAILURE;
	}
	
	// Attempt compiling shaders for GPU
	GLuint vertexShader;
	GLuint fragmentShader;
	try {
		compileShader(vertexShader, GL_VERTEX_SHADER, vShaderFilename);
		compileShader(fragmentShader, GL_FRAGMENT_SHADER, fShaderFilename);
	}
	catch(std::exception& e){
		std::cerr << e.what() << std::endl;
		glfwDestroyWindow(window); // destroys specified window
		glfwTerminate(); // destroys all windows
		return EXIT_FAILURE;
	}
	// Link compiled shaders into shader program object and activate it
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// If compilation failed, throw exception and print compile errors
	int linkSuccess;
	char infoLogBuffer[INFO_LOG_BUFFER_SIZE];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);
	if (!linkSuccess) {
		glGetProgramInfoLog(shaderProgram, INFO_LOG_BUFFER_SIZE, NULL, infoLogBuffer);
		std::cerr << "Shader program not linked\n" << infoLogBuffer << std::endl;
		glfwDestroyWindow(window); // destroys specified window
		glfwTerminate(); // destroys all windows
		return EXIT_FAILURE;
	}
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Allocate a vertex buffer object that will store vertices in GPU memory
	GLuint vbo;
	glGenBuffers(1, &vbo);
	// Indicate intent to use this buffer object for vertex attribute data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	/*
	// Define triangle's points
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	*/
	// Load vertices from obj file
	ObjFile objFile = ObjFile(objFilename);
	const std::vector<glm::vec3>* vertices = objFile.getVertices();
	// Send vertices to buffer binded to GL_ARRAY_BUFFER
	// Uses GL_STATIC_DRAW since vertex data won't be changed
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices->size(), vertices->data(), GL_STATIC_DRAW);

	// To store vertex attribute pointer configurations, use vertex array object (VAO)
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Tell openGL how to interpret vertex data in memory by communicating with the
	// vertex shader through vertex attributes
	// We want to pass vertices to location 0 (specified in the vertex shader).
	// Describe vertex array properties through parameters
	// Automatically takes data from VBO bound to GL_ARRAY_BUFFER
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Keep running until the window is told to close
	while (!glfwWindowShouldClose(window)) {
		glDrawArrays(GL_POINTS, 0, vertices->size());
		glfwSwapBuffers(window); // swap front and back buffers for no flicker
		glfwPollEvents(); // check if any events are triggered
	}

	// Deallocate resources:
	// Unbind the VBO and VAO and free them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glfwDestroyWindow(window); // destroys specified window
	glfwTerminate(); // destroys all windows

	return EXIT_SUCCESS;
}
