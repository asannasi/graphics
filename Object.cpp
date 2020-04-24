#include "Object.h"

Object::Object (const std::vector<glm::vec3>* v):vertices(v) {
	modelToWorld = glm::mat4(1.0f);
	spinning = false;

	// Allocate a vertex buffer object that will store vertices in GPU memory
	glGenBuffers(1, &vbo);
	// Indicate intent to use this buffer object for vertex attribute data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Send vertices to buffer binded to GL_ARRAY_BUFFER
	// Uses GL_STATIC_DRAW since vertex data won't be changed
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices->size(), vertices->data(), GL_STATIC_DRAW);

	// To store vertex attribute pointer configurations, use vertex array object (VAO)
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Tell openGL how to interpret vertex data in memory by communicating with the
	// vertex shader through vertex attributes
	// We want to pass vertices to location 0 (specified in the vertex shader).
	// Describe vertex array properties through parameters
	// Automatically takes data from VBO bound to GL_ARRAY_BUFFER
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind from the VBO.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Unbind from the VAO.
	glBindVertexArray(0);
}

Object::~Object(){
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

int Object::getNumVertices()
{
	return vertices->size();
}

GLuint Object::getVAO()
{
	return vao;
}

void Object::update() {
	if (spinning) {
		rotate(0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
}

void Object::setSpinning(bool spin) {
	spinning = spin;
}

bool Object::isSpinning() {
	return spinning;
}

void Object::rotate(float deg, glm::vec3 axis) {
	// Update the model matrix by multiplying a rotation matrix
	modelToWorld = glm::rotate(modelToWorld, glm::radians(deg), axis);
}

void Object::translate(GLfloat dist, glm::vec3 axis) {
	// Move model along axis by dist amount independent of transformations
	glm::vec4 translation = glm::vec4((axis * dist), 0.0f);
	modelToWorld[TRANSLATION_INDEX] = modelToWorld[TRANSLATION_INDEX] + translation;
}

void Object::uniformScale(GLfloat factor) {
	glm::vec3 scaleFactor = glm::vec3(factor, factor, factor);
	modelToWorld = glm::scale(modelToWorld, scaleFactor);
}

glm::mat4& Object::getModelMatrix() {
	return modelToWorld;
}