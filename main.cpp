/* 
 * This program uses openGL and C++ to render graphics.
 * It's written to reinforce personal self-studying.
 */

#include "main.h"

#define MAJOR_VERSION 3
#define MINOR_VERSION 3


namespace {
	// Set window properties
	int windowWidth = 800;
	int windowHeight = 600;
	const char* windowTitle = "Graphics Project";

	std::string vShaderFilename = "shader.vert";
	std::string fShaderFilename = "shader.frag";
	std::string objFilename = "a.obj";

	const int numObjects = 2;
	Object* objects[numObjects];

	const float SCALE_FACTOR = 0.5f;
	const float MOVE_DIST = 1.0f;
};

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	// Tell openGL the window dimensions (can be different from glfw's)
	glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// Check for key press and then check if uppercase or lowercase key by checking shift
	if (action == GLFW_PRESS) {
		if (mods == GLFW_MOD_SHIFT) {
			switch (key) {
			case(GLFW_KEY_COMMA):
				objects[0]->uniformScale(SCALE_FACTOR);
				break;
			case(GLFW_KEY_PERIOD):
				objects[0]->uniformScale(1.0f + SCALE_FACTOR);
				break;
			default:
				break;
			}
		}
		else {
			switch (key) {
			case (GLFW_KEY_ESCAPE):
				// Close window
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
			case(GLFW_KEY_R):
				// Spin object
				if (objects[0]->isSpinning()) {
					objects[0]->setSpinning(false);
				}
				else {
					objects[0]->setSpinning(true);
				}
				break;
			// Movement Keys WASD
			case GLFW_KEY_A:
				objects[0]->translate(MOVE_DIST, glm::vec3(-1, 0, 0));
				break;
			case GLFW_KEY_D:
				objects[0]->translate(MOVE_DIST, glm::vec3(1, 0, 0));
				break;
			case GLFW_KEY_W:
				objects[0]->translate(MOVE_DIST, glm::vec3(0, 1, 0));
				break;
			case GLFW_KEY_S:
				objects[0]->translate(MOVE_DIST, glm::vec3(0, -1, 0));
				break;
			default:
				break;
			}
		}
	}
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
	windowResizeCallback(window, windowWidth, windowHeight);

	// Set the callback function when a key is pressed
	glfwSetKeyCallback(window, keyCallback);

	// Initialize GLEW, which is a library that checks supported openGL 
	// extensions at runtime on the target platform.
	glewExperimental = GL_TRUE;
	if (glewInit() || !glGenVertexArrays) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate(); // free GLFW window before exiting
		return EXIT_FAILURE;
	}

	Renderer renderer;
	try {
		ShaderFile vertFile = ShaderFile(vShaderFilename);
		ShaderFile fragFile = ShaderFile(fShaderFilename);
		renderer = Renderer(vertFile, fragFile, windowWidth, windowHeight);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		glfwDestroyWindow(window); // destroys specified window
		glfwTerminate(); // destroys all windows
		return EXIT_FAILURE;
	}

	// Load vertices from obj file
	ObjFile objFile = ObjFile(objFilename);
	Object dragon = Object(objFile.getVertices());
	objects[0] = &dragon;

	// Keep running until the window is told to close
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.render(dragon);
		glfwSwapBuffers(window); // swap front and back buffers for no flicker
		glfwPollEvents(); // check if any events are triggered
	}

	// Deallocate resources:
	// Unbind the VBO and VAO and free them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glfwDestroyWindow(window); // destroys specified window
	glfwTerminate(); // destroys all windows

	return EXIT_SUCCESS;
}
