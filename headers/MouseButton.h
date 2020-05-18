#pragma once

#include <GLFW/glfw3.h>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/string_cast.hpp>

class MouseButton {
private:
	// Used to find the midpoint of the window to transform coordinates
	static const int MID_DIVISOR = 2;

	// Used to calculate Pythagoras theorem squares
	static const int SQ_EXP = 2;

	// Axis indices in glm vector
	static const int Y_INDEX = 1;
	static const int Z_INDEX = 2;

	// Scales the distance between two cursor positions for translation 
	float dragTranslateFactor;

	// Scales up the angle between two cursor positions for rotation
	float dragRotateFactor;
	
	// Small changes are ignored if under this threshold.
	// Ex. Dragging the mouse but staying in the same position.
	float dragThreshold;

	// Cursor has state for whether it is dragging and will store
	// the last recorded position of the cursor.
	bool dragging = false;
	glm::vec3 startVec = glm::vec3(0, 0, 0);

	// Precalculated values used to calculate transformation 
	// relative to mouse position.
	int midWindowWidth;
	int midWindowHeight;
	double sphereRadiusSq;

	// Adds z component to screen vector based on where point would be on 
	// a virtual 3D sphere.
	glm::vec3 mousePosToScreenVector(double& x, double& y);

	// This function adds a z-component (depth) to the screen vector to 
	// map coordinates onto a virtual 3D sphere for rotation.
	void screenVectorToSphereVector(glm::vec3& screenVector);

public:
	MouseButton(int windowWidth, int windowHeight, 
		float dragThreshold, float dragRotateFactor, float dragTranslateFactor);

	// Recalculates precomputed values for coordinate transformation
	void updateWindowSize(int windowWidth, int windowHeight);

	// Records the position on press and MouseButton will go into dragging state
	// until release.
	void press(GLFWwindow* window);
	void release();

	// These functions find the current mouse position and compare it with 
	// the stored starting position if in a dragging state. The magnitude and 
	// axis for the transformation are stored in the paramters, but they could 
	// be invalid if the magnitude is less than the threshold or if the axis 
	// is NaN when the mouse stays still. False is returned if invalid.
	bool calcDragTranslationInfo(GLFWwindow* window, float& dist, glm::vec3& axis);
	bool calcDragRotationInfo(GLFWwindow* window, float& deg, glm::vec3& axis);
};
