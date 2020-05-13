#pragma once

#include "../headers/Mouse.h"

Mouse::Mouse(int windowWidth, int windowHeight, float dragThreshold, int dragRotateFactor) : 
	dragThreshold(dragThreshold), dragRotateFactor(dragRotateFactor) {
	
	updateWindowSize(windowWidth, windowHeight);
}

void Mouse::leftButtonPress(GLFWwindow* window){
	dragging = true;
	double startX = 0;
	double startY = 0;
	glfwGetCursorPos(window, &startX, &startY);
	prevMouseVec = mousePosToSphereVector(startX, startY);
}

void Mouse::leftButtonRelease() {
	dragging = false;
}

// This function changes the mouse position on the screen into
// coordinates on a virtual 3D sphere for rotation. The mouse
// position coordinates start from the upper left of the screen
// and range x:[0, windowWidth] and y:[0, windowHeight].
glm::vec3 Mouse::mousePosToSphereVector(double& x, double& y) {
	x = x - midWindowWidth;
	y = (y - midWindowHeight) * -1;
	double z = glm::sqrt(sphereRadiusSq - glm::pow(y, SQ_EXP));
	return glm::vec3(x, y, z);
}

void Mouse::updateWindowSize(int windowWidth, int windowHeight) {
	midWindowHeight = windowWidth / MID_DIVISOR;
	midWindowWidth = windowHeight / MID_DIVISOR;
	sphereRadiusSq = glm::pow(windowHeight, SQ_EXP);
}

bool Mouse::calcRotationInfoForDrag(GLFWwindow* window, float& deg, glm::vec3& rotationAxis) {
	assert(dragging);
	double endX = 0;
	double endY = 0;
	glfwGetCursorPos(window, &endX, &endY);
	glm::vec3 endVec = mousePosToSphereVector(endX, endY);
	rotationAxis = glm::normalize(glm::cross(prevMouseVec, endVec));
	deg = glm::angle(glm::normalize(prevMouseVec), glm::normalize(endVec));
	if (deg < dragThreshold || glm::all(glm::isnan(rotationAxis))) {
		return false;
	}
	deg *= dragRotateFactor;
	prevMouseVec = endVec;
	return true;
}

bool Mouse::isDragging() {
	return dragging;
}