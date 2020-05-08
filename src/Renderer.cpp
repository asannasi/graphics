#include "../headers/Renderer.h"

Renderer::Renderer (ShaderFile vertFile, ShaderFile fragFile, int width, int height) {
	mode = RenderMode::FULL;
	shaders = Shaders(vertFile, fragFile);	// Can throw exception
	camera = Camera(width, height);
	shaders.setUniformProjView(camera.getProjViewMatrix());
}

void Renderer::setAspectRatio(int width, int height) {
	camera.setAspectRatio(width, height);
	shaders.setUniformProjView(camera.getProjViewMatrix());
}

void Renderer::setRenderModePointCloud() {
	mode = RenderMode::POINTCLOUD;
}

void Renderer::setRenderModeFull() {
	mode = RenderMode::FULL;
}

void Renderer::render(Object& obj) {
	// Update the object's model matrix and then pass it to the
	// shader. Then bind the vao for the object and draw it.
	obj.update();
	shaders.setUniformModel(obj.getModelMatrix());
	glBindVertexArray(obj.getVAO());
	// Check rendering mode
	if (mode == RenderMode::POINTCLOUD) {
		glDrawArrays(GL_POINTS, 0, obj.getNumVertices());
	}
	else {
		glDrawElements(GL_TRIANGLES, obj.getNumFaces(), GL_UNSIGNED_INT, 0);
	}
	// Unbind VAO
	glBindVertexArray(0);
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