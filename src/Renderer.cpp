#include "../headers/Renderer.h"

Renderer::Renderer(ShaderFile vertFile, ShaderFile fragFile, int width, int height) : 
	shaders(vertFile, fragFile), camera(width, height) {

	// Enable z-buffer to make sure pixels overlap correctly
	glEnable(GL_DEPTH_TEST);
}

void Renderer::setAspectRatio(int width, int height) {
	camera.setAspectRatio(width, height);
	shaders.setUniformMatrix("projView", camera.getProjViewMatrix());
}

void Renderer::render(Object& obj) {
	shaders.load();
	
	shaders.setUniformMatrix("model", obj.getModelMatrix());
	shaders.setUniformMatrix("projView", camera.getProjViewMatrix());
	shaders.setUniformVec("color", obj.getColor());

	obj.draw();
}

void Renderer::render(Object& obj, Object& light) {
	shaders.load();

	shaders.setUniformMatrix("model", obj.getModelMatrix());
	shaders.setUniformMatrix("projView", camera.getProjViewMatrix());
	shaders.setUniformVec("color", obj.getColor());
	shaders.setUniformVec("lightColor", light.getColor());
	shaders.setUniformVec("lightPos", light.getCenterInWorld());
	shaders.setUniformVec("viewerPos", camera.getViewerPos());

	obj.draw();
}

void Renderer::rotateCamera(float deg, glm::vec3& axis) {
	camera.rotate(deg, axis);
	shaders.setUniformMatrix("projView", camera.getProjViewMatrix());
}