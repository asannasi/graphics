#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

#include "Shaders.h"
#include "Object.h"
#include "Camera.h"

class Renderer
{
private:
	// Responsible for updating view and projection matrices
	Camera camera;

	// Object to hold shaders and their state
	Shaders shaders;

public:
	Renderer() = default;
	Renderer(ShaderFile vertFile, ShaderFile fragFile, int width, int height);
	void setAspectRatio(int width, int height);
	void render(Object& obj);
	~Renderer();
};

