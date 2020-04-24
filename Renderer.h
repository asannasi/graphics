#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

#include "Shaders.h"
#include "Object.h"

class Renderer
{
private:
	// Defaults for creating projection matrix
	float fov = 45.0f; // field of view
	float aspectRatio = 0;
	float near = 0.1f;
	float far = 100.0f;

	// View matrix that transforms world space to view space
	glm::mat4 view;
	// Projection matrix that transforms view space into clip space
	glm::mat4 proj;

	// Object to hold shaders and their state
	Shaders shaders;

public:
	Renderer() = default;
	Renderer(ShaderFile vertFile, ShaderFile fragFile, int width, int height);
	void setAspectRatio(int width, int height);
	void render(Object& obj);
	void setModelMatrix(glm::mat4& modeltoWorld);
	void setViewMatrix(glm::vec3& pos, glm::vec3& target, glm::vec3& up);
	void setProjMatrix(float& fov, float& aspectRatio, float& near, float& far);
	~Renderer();
};

