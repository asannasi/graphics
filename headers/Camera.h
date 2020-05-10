#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera
{
private:
	// Defaults for creating the view matrix
	// Vector for where the camera is in world space
	glm::vec3 position = glm::vec3(0, 0, 5);
	// Vector for where the camera is looking at in world space.
	// This is the origin of the scene.
	glm::vec3 target = glm::vec3(0, 0, 0);
	// Vector for the up direction of the camera in world space
	glm::vec3 up = glm::vec3(0, 1, 0);
	// View matrix that transforms world space to view space
	glm::mat4 view;

	// Defaults for creating projection matrix
	float fov = 45.0f; // field of view
	float aspectRatio;
	float near = 0.1f;
	float far = 100.0f;
	// Projection matrix that transforms view space into clip space
	glm::mat4 proj;

public:
	Camera(int width, int height);
	~Camera();

	void setAspectRatio(int width, int height);

	glm::mat4 getProjViewMatrix();
	void rotate(float deg, glm::vec3 axis);
};