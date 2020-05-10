#include "../headers/Renderer.h"

Renderer::Renderer(ShaderFile vertFile, ShaderFile fragFile, int width, int height) : 
	shaders(vertFile, fragFile), camera(width, height) {
	glEnable(GL_DEPTH_TEST); // enable zbuffer to make sure pixels overlap correctly
	shaders.setUniformProjView(camera.getProjViewMatrix());
}

void Renderer::setAspectRatio(int width, int height) {
	camera.setAspectRatio(width, height);
	shaders.setUniformProjView(camera.getProjViewMatrix());
}

void Renderer::render(Object& obj) {
	// Update the object's model matrix and then pass it to the
	// shader. Then bind the vao for the object and draw it.
	obj.update();
	shaders.load();
	shaders.setUniformModel(obj.getModelMatrix());
	shaders.setUniformProjView(camera.getProjViewMatrix());
	obj.draw();
}

void Renderer::rotateCameraLeft(float deg) {
	camera.rotate(deg, glm::vec3(0,1,0));
	shaders.setUniformProjView(camera.getProjViewMatrix());
}

void Renderer::rotateCameraRight(float deg) {
	camera.rotate(deg, glm::vec3(0, -1, 0));
	shaders.setUniformProjView(camera.getProjViewMatrix());
}

Renderer::~Renderer() {}