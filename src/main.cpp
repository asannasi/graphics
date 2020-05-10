/* 
 * This program uses openGL and C++ to render graphics.
 * It's written to reinforce personal self-studying.
 */

#include "../headers/main.h"

namespace {
	// Set openGL version 
	constexpr int MAJOR_VERSION = 3;
	constexpr int MINOR_VERSION = 3;

	// Set window properties
	int windowWidth = 800;
	int windowHeight = 600;
	const char* windowTitle = "Graphics Project";

	std::string vShaderFilenameNorm = ".\\shaders\\vert\\normalsShader.vert";
	std::string fShaderFilenameNorm = ".\\shaders\\frag\\normalsShader.frag";
	std::string vShaderFilenameVert = ".\\shaders\\vert\\verticesShader.vert";
	std::string fShaderFilenameVert = ".\\shaders\\frag\\verticesShader.frag";

	const int numObjects = 2;
	std::string objFilenames[] = { "a.obj", "sphere.obj" };
	ObjFile* objFiles[numObjects];
	Object* objects[numObjects];
	Object* currObj;

	const float SCALE_FACTOR = 0.5f;
	const float MOVE_DIST = 1.0f;
	const float CAMERA_ROTATE_ANG = 45.0f;

	Renderer* vertRenderer;
	Renderer* normRenderer;
	Renderer* currRenderer;
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
			// Scale object
			case(GLFW_KEY_COMMA):
				currObj->uniformScale(SCALE_FACTOR);
				break;
			case(GLFW_KEY_PERIOD):
				currObj->uniformScale(1.0f + SCALE_FACTOR);
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
			case (GLFW_KEY_F1):
				currObj = objects[0];
				break;
			case (GLFW_KEY_F2):
				currObj = objects[1];
				break;
			case (GLFW_KEY_1):
				currRenderer = vertRenderer;
				break;
			case (GLFW_KEY_2):
				currRenderer = normRenderer;
				break;
			case (GLFW_KEY_P):
				// Change render mode
				currRenderer->setRenderModePointCloud();
				break;
			case (GLFW_KEY_F):
				// Change render mode
				currRenderer->setRenderModeFull();
				break;
			case(GLFW_KEY_R):
				// Spin object
				if (currObj->isSpinning()) {
					currObj->setSpinning(false);
				}
				else {
					currObj->setSpinning(true);
				}
				break;
			// Movement Keys WASD
			case GLFW_KEY_A:
				currObj->translate(MOVE_DIST, glm::vec3(-1, 0, 0));
				break;
			case GLFW_KEY_D:
				currObj->translate(MOVE_DIST, glm::vec3(1, 0, 0));
				break;
			case GLFW_KEY_W:
				currObj->translate(MOVE_DIST, glm::vec3(0, 1, 0));
				break;
			case GLFW_KEY_S:
				currObj->translate(MOVE_DIST, glm::vec3(0, -1, 0));
				break;
			// Rotate camera
			case GLFW_KEY_Q:
				currRenderer->rotateCameraLeft(CAMERA_ROTATE_ANG);
				break;
			case GLFW_KEY_E:
				currRenderer->rotateCameraRight(CAMERA_ROTATE_ANG);
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
	if (glewInit() || !glGenVertexArrays || !glGenBuffers) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate(); // free GLFW window before exiting
		return EXIT_FAILURE;
	}

	try {
		// Load simple shaders and create renderer
		ShaderFile vertFile = ShaderFile(vShaderFilenameVert);
		ShaderFile fragFile = ShaderFile(fShaderFilenameVert);
		vertRenderer = new Renderer(vertFile, fragFile, windowWidth, windowHeight);
		
		// Load shaders with normal coloring and create renderer
		vertFile = ShaderFile(vShaderFilenameNorm);
		fragFile = ShaderFile(fShaderFilenameNorm);
		normRenderer = new Renderer(vertFile, fragFile, windowWidth, windowHeight);

		// Load vertices from obj file
		objFiles[0] = new ObjFile(objFilenames[0]);
		objFiles[1] = new ObjFile(objFilenames[1]);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		delete vertRenderer;
		delete normRenderer;
		delete objFiles[0];
		delete objFiles[1];
		glfwDestroyWindow(window); // destroys specified window
		glfwTerminate(); // destroys all windows
		return EXIT_FAILURE;
	}
	
	// Initialize objects from points data
	objects[0] = new Object(*objFiles[0]);
	objects[1] = new Object(*objFiles[1]);

	// Set the current state
	currObj = objects[0];
	currRenderer = normRenderer;

	// Keep running until the window is told to close
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		currRenderer->render(*objects[0]);
		currRenderer->render(*objects[1]);
		glfwSwapBuffers(window); // swap front and back buffers for no flicker
		glfwPollEvents(); // check if any events are triggered
	}

	// Deallocate resources:
	// Unbind the VBO and VAO and free them
	delete vertRenderer;
	delete normRenderer;
	delete objFiles[0];
	delete objFiles[1];
	delete objects[0];
	delete objects[1];
	glfwDestroyWindow(window); // destroys specified window
	glfwTerminate(); // destroys all windows

	return EXIT_SUCCESS;
}
