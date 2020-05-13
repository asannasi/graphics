#pragma once

#include <GLFW/glfw3.h>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/string_cast.hpp>

class Mouse {
private:
	static const int MID_DIVISOR = 2;
	static const int SQ_EXP = 2;

	int dragRotateFactor;
	int dragThreshold;

	bool dragging = false;
	glm::vec3 prevMouseVec = glm::vec3(0,0,0);

	int midWindowWidth;
	int midWindowHeight;

	double sphereRadiusSq;

public:
	Mouse(int windowWidth, int windowHeight, float dragThreshold, int dragRotateFactor);
	void leftButtonPress(GLFWwindow* window);
	void leftButtonRelease();
	glm::vec3 mousePosToSphereVector(double& x, double& y);
	void updateWindowSize(int windowWidth, int windowHeight);
	bool calcRotationInfoForDrag(GLFWwindow* window, float& deg, glm::vec3& rotationAxis);
	bool isDragging();
};
