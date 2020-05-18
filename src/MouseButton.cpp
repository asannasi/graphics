#pragma once

#include "../headers/MouseButton.h"

MouseButton::MouseButton(int windowWidth, int windowHeight, 
	float dragThreshold, float dragRotateFactor, float dragTranslateFactor) : 
	dragThreshold(dragThreshold), 
	dragRotateFactor(dragRotateFactor), 
	dragTranslateFactor(dragTranslateFactor) {
	updateWindowSize(windowWidth, windowHeight);
}

// Mouse position coordinates start from the upper left of the screen
// and have range x:[0, windowWidth] and y:[0, windowHeight]. This function
// shifts range to x:[-windowWidth/2:windowWidth/2] and
// y:[-windowHeight/2:windowHeight/2].
glm::vec3 MouseButton::mousePosToScreenVector(double& x, double& y) {
	x = x - midWindowWidth;
	y = (y - midWindowHeight) * -1;
	return glm::vec3(x, y, 0);
}

// This function uses the Pythagorean Theorem.
void MouseButton::screenVectorToSphereVector(glm::vec3& worldVector) {
	worldVector[Z_INDEX] = (float) glm::sqrt(sphereRadiusSq - 
		glm::pow(worldVector[Y_INDEX], SQ_EXP));
}

void MouseButton::updateWindowSize(int windowWidth, int windowHeight) {
	midWindowHeight = windowWidth / MID_DIVISOR;
	midWindowWidth = windowHeight / MID_DIVISOR;
	sphereRadiusSq = glm::pow(windowHeight, SQ_EXP);
}

void MouseButton::press(GLFWwindow* window){
	dragging = true;
	double startX, startY;
	glfwGetCursorPos(window, &startX, &startY);
	startVec = mousePosToScreenVector(startX, startY);
}

void MouseButton::release() {
	dragging = false;
}

bool MouseButton::calcDragTranslationInfo(GLFWwindow* window, float& dist, glm::vec3& axis) {
	if (!dragging) {
		return false;
	}

	// Get the current mouse position
	double endX, endY;
	glfwGetCursorPos(window, &endX, &endY);
	glm::vec3 endVec = mousePosToScreenVector(endX, endY);

	// The difference vector is a vector between the start and end mouse positions.
	glm::vec3 diff = endVec - startVec;
	axis = glm::normalize(diff);
	dist = glm::length(diff) * dragTranslateFactor;

	// Filter result of calculation
	if (dist < dragThreshold || glm::all(glm::isnan(axis))) {
		return false;
	}

	startVec = endVec;
	return true;
}

bool MouseButton::calcDragRotationInfo(GLFWwindow* window, float& deg, glm::vec3& axis) {
	if (!dragging) {
		return false;
	}

	// Get current mouse position
	double endX, endY;
	glfwGetCursorPos(window, &endX, &endY);
	glm::vec3 endVec = mousePosToScreenVector(endX, endY);

	// Map to sphere vectors to rotate around an axis using the cross product
	screenVectorToSphereVector(startVec);
	screenVectorToSphereVector(endVec);

	axis = glm::normalize(glm::cross(startVec, endVec));
	deg = glm::angle(glm::normalize(startVec), glm::normalize(endVec));

	// Filter result of calculation
	if (deg < dragThreshold || glm::all(glm::isnan(axis))) {
		return false;
	}

	deg *= dragRotateFactor;
	startVec = endVec;
	return true;
}