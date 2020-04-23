#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

#include "Shaders.h"

class Renderer
{
private:
	// View matrix that transforms world space to view space
	glm::mat4 view;
	// Projection matrix that transforms view space into clip space
	glm::mat4 proj;

	// Object to hold shaders and their state
	Shaders shaders;

public:
	Renderer(std::string vShaderFilename, std::string fShaderFilename, int width, int height);
	void render(const std::vector<glm::vec3>* vertices, glm::mat4 modelToWorld);
	void setViewMatrix(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
	void setProjMatrix(float fov, float aspectRatio, float near, float far);
	~Renderer();
};

