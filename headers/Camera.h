#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera
{
private:
	// Defaults for creating the view matrix
	glm::vec3 position = glm::vec3(0, 0, 5); // Where the camera is in world space
	glm::vec3 target   = glm::vec3(0, 0, 0); // Where the camera looks at in world space
	glm::vec3 up       = glm::vec3(0, 1, 0); // Up direction of the camera in world space

	// Defaults for creating projection matrix
	float fieldOfView = 45.0f;
	float near = 0.1f;
	float far = 100.0f;
	float aspectRatio; // width/height

	glm::mat4 view;	    // View matrix that transforms world space to view space
	glm::mat4 proj;	    // Projection matrix that transforms view space into clip space
	glm::mat4 projView;	// Precomputed proj*view matrix

	inline void updateProjView(); // Recalculates proj*view

public:
	Camera(int windowWidth, int windowHeight);

	glm::mat4& getProjViewMatrix();

	glm::vec3 getViewerPos();

	// Calculates new aspect ratio and updates proj matrix
	void setAspectRatio(int windowWidth, int windowHeight);

	// Rotates camera along axis for given degrees by updated view matrix
	void rotate(float deg, glm::vec3 axis);
};