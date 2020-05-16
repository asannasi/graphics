#pragma once

#include "Shaders.h"
#include "Camera.h"
#include "Object.h"
#include "Cube.h"

/*
 * This class is responsible for rendering objects with the latest shader
 * and camera values. It basically handles the overall graphics pipeline.
 */
class Renderer
{
private:
	// Interface with shaders to set uniform matrices
	Shaders shaders;

	// Interface to update view and projection matrices and set them in shaders
	Camera camera;

public:
	// Constructor can throw an exception if shaders could not be compiled
	Renderer(ShaderFile vertFile, ShaderFile fragFile, int width, int height);
	~Renderer();

	void setAspectRatio(int width, int height);
	void render(Object& obj);
	void rotateCamera(float deg, glm::vec3& axis);
};
