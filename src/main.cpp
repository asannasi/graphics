/* 
 * This program uses openGL and C++ to render graphics.
 */

#include "../headers/main.h"

namespace {
	// OpenGL version MAJOR.MINOR (i.e. 3.3)
	const int MAJOR_VERSION = 3;
	const int MINOR_VERSION = 3;

	// Set window properties
	int windowWidth = 800;
	int windowHeight = 600;
	const char* windowTitle = "Graphics Project";

	// Constants for object manipulation
	const float SCALE_FACTOR = 0.5f;
	const float MOVE_DIST = 1.0f;
	const float CAMERA_ROTATE_ANG = 20.0f;

	// Direction vectors
	glm::vec3 UP = glm::vec3(0, 1, 0);
	glm::vec3 DOWN = glm::vec3(0, -1, 0);
	glm::vec3 LEFT = glm::vec3(-1, 0, 0);
	glm::vec3 RIGHT = glm::vec3(1, 0, 0);

	// Filenames of shader sets (vertex shader & fragment shader)
	std::string vShaderFilenameNorm = ".\\shaders\\vert\\normalsShader.vert";
	std::string fShaderFilenameNorm = ".\\shaders\\frag\\normalsShader.frag";
	std::string vShaderFilenameVert = ".\\shaders\\vert\\verticesShader.vert";
	std::string fShaderFilenameVert = ".\\shaders\\frag\\verticesShader.frag";
	
	// Renderers for each shader set
	Renderer* vertRenderer;
	Renderer* normRenderer;

	const int NUM_OBJECTS = 2;
	Object* objects[NUM_OBJECTS];

	const int NUM_OBJFILES = 2;
	std::string objFilenames[] = { "a.obj", "sphere.obj" };
	ObjFile objFiles[NUM_OBJFILES];

	// These are the current selected instances, usually those 
	// controllable by keys
	Object* currObj;
	Renderer* currRenderer;

	const float MOUSE_DRAG_THRESHOLD = 0.05f;
	const int MOUSE_DRAG_ROTATE_FACTOR = 90;
	Mouse* mouse;
};

// Tell openGL the new window dimensions.
// It can be different from GLFW's.
void windowResizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	mouse->updateWindowSize(width, height);
}

// This function defines how users interact with program through key presses
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// Check for key press and then check if uppercase or lowercase key by checking shift
	if (action == GLFW_PRESS) {
		if (mods == GLFW_MOD_SHIFT) {
			switch (key) {
			// Scale current object with > (shift + ,) and < (shift + .) keys
			case(GLFW_KEY_COMMA):
				assert(SCALE_FACTOR <= 1.0f);
				currObj->uniformScale(SCALE_FACTOR);
				break;
			case(GLFW_KEY_PERIOD):
				assert(SCALE_FACTOR <= 1.0f);
				currObj->uniformScale(1.0f + SCALE_FACTOR);
				break;
			default:
				break;
			}
		}
		else {
			switch (key) {
			// ESC closes window
			case (GLFW_KEY_ESCAPE):
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
			
			// Switch current selected object with function keys
			case (GLFW_KEY_F1):
				currObj = objects[0];
				break;
			case (GLFW_KEY_F2):
				currObj = objects[1];
				break;

			// Switch current selected renderer with num keys
			case (GLFW_KEY_1):
				currRenderer = vertRenderer;
				break;
			case (GLFW_KEY_2):
				currRenderer = normRenderer;
				break;

			// Change selected object's draw mode
			case (GLFW_KEY_P):
				currObj->setDrawModePointCloud();
				break;
			case (GLFW_KEY_F):
				currObj->setDrawModeMesh();
				break;

			// Make selected object spin
			case(GLFW_KEY_R):
				currObj->setSpinning(!currObj->isSpinning());
				break;

			// Move selected object with WASD
			case GLFW_KEY_W:
				currObj->translate(MOVE_DIST, UP);
				break;
			case GLFW_KEY_A:
				currObj->translate(MOVE_DIST, LEFT);
				break;
			case GLFW_KEY_S:
				currObj->translate(MOVE_DIST, DOWN);
				break;
			case GLFW_KEY_D:
				currObj->translate(MOVE_DIST, RIGHT);
				break;

			// Rotate camera
			case GLFW_KEY_Q:
				currRenderer->rotateCamera(CAMERA_ROTATE_ANG, LEFT);
				break;
			case GLFW_KEY_E:
				currRenderer->rotateCamera(CAMERA_ROTATE_ANG, RIGHT);
				break;

			default:
				break;
			}
		} // end of IF checking shift key
	} // end of IF checking key press
}

// Call the corresponding Mouse object methods
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			mouse->leftButtonPress(window);
		}
	}
	else if (action == GLFW_RELEASE) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			mouse->leftButtonRelease();
		}
	}
}

// Run the interactive graphics application
int main(void) {
	// Make sure platform is not OSX
	#ifdef __APPLE__
	std::cerr << "Program supports Windows, not OSX." << std::endl;
	return EXIT_FAILURE;
	#endif

	// Initialize GLFW, which is a utility library for openGL
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return EXIT_FAILURE;
	}

	// Check openGL version to be 3.3 and only use core functions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW window, which encapsulates a window and openGL context
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	if (!window) {
		std::cerr << "Failed to initialize GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Make the openGL context for the created window the current one.
	// A context stores openGL's state and is thread-local.
	glfwMakeContextCurrent(window);

	// Set callback functions
	glfwSetFramebufferSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	// Set window's background default color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Initialize GLEW, which is a library that checks supported openGL 
	// extensions at runtime on the target platform. Check if glew was
	// initialized correctly by checking if function pointers exists.
	glewExperimental = GL_TRUE;
	if (glewInit() || !glGenVertexArrays || !glGenBuffers) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Possible exceptions when opening files and compiling shaders
	try {
		// Load simple shaders and create renderer
		ShaderFile vertFile = ShaderFile(vShaderFilenameVert);
		ShaderFile fragFile = ShaderFile(fShaderFilenameVert);
		vertRenderer = new Renderer(vertFile, fragFile, windowWidth, windowHeight);
		
		// Load shaders with normal coloring and create renderer
		vertFile = ShaderFile(vShaderFilenameNorm);
		fragFile = ShaderFile(fShaderFilenameNorm);
		normRenderer = new Renderer(vertFile, fragFile, windowWidth, windowHeight);

		objFiles[0] = ObjFile(objFilenames[0]);
		objFiles[1] = ObjFile(objFilenames[1]);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		delete vertRenderer;
		delete normRenderer;
		glfwDestroyWindow(window);
		glfwTerminate(); // destroys all windows
		return EXIT_FAILURE;
	}
	
	objects[0] = new Object(objFiles[0]);
	objects[1] = new Object(objFiles[1]);
	Cube* c = new Cube(1.0f);

	// Set the current state
	currObj = objects[0];
	currRenderer = normRenderer;

	mouse = new Mouse(windowWidth, windowHeight, 
		MOUSE_DRAG_THRESHOLD, MOUSE_DRAG_ROTATE_FACTOR);

	// Keep running until the window is told to close
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Dragging the mouse should rotate the current object
		if (mouse->isDragging()) {
			float deg = 0.0f;
			glm::vec3 rotationAxis;
			bool infoIsValid = mouse->calcRotationInfoForDrag(window, deg, rotationAxis);
			if (infoIsValid) {
				currObj->rotate(deg, rotationAxis);
			}
		}

		for (int i = 0; i < NUM_OBJECTS; ++i) {
			objects[i]->update();
			currRenderer->render(*objects[i]);
		}
		vertRenderer->render(*c);

		glfwSwapBuffers(window); // swap front and back buffers for no flicker
		glfwPollEvents(); // check if any events are triggered
	}

	// End of program so deallocate resources
	delete mouse;
	delete vertRenderer;
	delete normRenderer;
	for (int i = 0; i < NUM_OBJECTS; i++) {
		delete objects[i];
	}
	glfwDestroyWindow(window);
	glfwTerminate(); // destroys all windows

	return EXIT_SUCCESS;
}
