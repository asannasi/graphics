#include "Renderer.h"

Renderer::Renderer (ShaderFile vertFile, ShaderFile fragFile, int width, int height) {
	// Can throw exception
	shaders = Shaders(vertFile, fragFile);

	// Vector for where the camera is in world space
	glm::vec3 cameraPos(0, 0, 5);

	// Vector for where the camera is looking at in world space.
	// This is the origin of the scene.
	glm::vec3 cameraTarget(0, 0, 0);

	// Vector for the up direction of the camera in world space
	glm::vec3 cameraUp(0, 1, 0);

	setViewMatrix(cameraPos, cameraTarget, cameraUp);

	float fov = 45.0f; // field of view
	float aspectRatio = (float)width / (float)height;
	float near = 0.1f;
	float far = 100.0f;

	setProjMatrix(fov, aspectRatio, near, far);
}

void Renderer::setAspectRatio(int width, int height) {
	float fov = 45.0f; // field of view
	float aspectRatio = (float)width / (float)height;
	float near = 0.1f;
	float far = 100.0f;
	setProjMatrix(fov, aspectRatio, near, far);
}

void Renderer::render(Object& obj) {
	glBindVertexArray(obj.getVAO());
	glPointSize(5);
	glDrawArrays(GL_POINTS, 0, obj.getNumVertices());
	glBindVertexArray(0);
}

void Renderer::setModelMatrix(glm::mat4 modeltoWorld) {
	shaders.setUniformModel(modeltoWorld);
}

void Renderer::setViewMatrix(glm::vec3 pos, glm::vec3 target, glm::vec3 up) {
	view = glm::lookAt(pos, target, up);
	shaders.setUniformView(view);
}

void Renderer::setProjMatrix(float fov, float aspectRatio, float near, float far) {
	proj = glm::perspective(fov, aspectRatio, near, far);
	shaders.setUniformProj(proj);
}

Renderer::~Renderer() {}