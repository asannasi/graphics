#include "../headers/Renderer.h"

Renderer::Renderer(ShaderFile vertFile, ShaderFile fragFile, int width, int height) : 
	shaders(vertFile, fragFile), camera(width, height) {

	// Enable z-buffer to make sure pixels overlap correctly
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer() {}

void Renderer::setAspectRatio(int width, int height) {
	camera.setAspectRatio(width, height);
	shaders.setUniformProjView(camera.getProjViewMatrix());
}

void Renderer::render(Object& obj) {
	shaders.load();
	shaders.setUniformModel(obj.getModelMatrix());
	shaders.setUniformProjView(camera.getProjViewMatrix());
	shaders.setUniformColor(obj.getColor());
	shaders.setUniformLight();
	obj.draw();
}

void Renderer::rotateCamera(float deg, glm::vec3& axis) {
	camera.rotate(deg, axis);
	shaders.setUniformProjView(camera.getProjViewMatrix());
}