#include "Renderer.h"

Renderer::Renderer (ShaderFile vertFile, ShaderFile fragFile, int width, int height) {
	shaders = Shaders(vertFile, fragFile);	// Can throw exception
	camera = Camera(width, height);
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
	shaders.setUniformModel(obj.getModelMatrix());
	glBindVertexArray(obj.getVAO());
	glDrawArrays(GL_POINTS, 0, obj.getNumVertices());
	glBindVertexArray(0);
}

Renderer::~Renderer() {}