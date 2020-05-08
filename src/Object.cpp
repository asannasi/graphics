#include "../headers/Object.h"

Object::Object(const std::vector<glm::vec3>* v, const std::vector<glm::vec3>* n, 
	const std::vector<unsigned int>* f) :vertices(v), normals(n), faces(f) {
	modelToWorld = glm::mat4(1.0f); // Identity Matrix
	spinning = false;

	// To store vertex attribute pointer configurations, use vertex array object (VAO)
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Allocate buffer objects that will store data in GPU memory
	glGenBuffers(NUM_BUFFERS, buffers);
	bufferData(vertices, VERTEX_ATTR_INDEX);
	bufferData(normals, NORMAL_ATTR_INDEX);
	bufferData(faces, FACES_ATTR_INDEX);

	// Unbind from the VAO.
	glBindVertexArray(0);
}

Object::~Object(){
	glDeleteBuffers(NUM_BUFFERS, buffers);
	glDeleteVertexArrays(1, &vao);
}

int Object::getNumVertices() {
	return vertices->size();
}

int Object::getNumFaces() {
	return faces->size();
}

GLuint Object::getVAO() {
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

GLuint Object::getFacesEBO() {
	return buffers[FACES_ATTR_INDEX];
}

void Object::bufferData(const std::vector<glm::vec3>* data, int index) {
	// Indicate intent to use this buffer object for attribute data
	glBindBuffer(GL_ARRAY_BUFFER, buffers[index]);

	// Send data to buffer binded to GL_ARRAY_BUFFER
	// Uses GL_STATIC_DRAW since data won't be changed
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * data->size(), data->data(), GL_STATIC_DRAW);

	// Tell openGL how to interpret data in memory by communicating with the
	// shader through attributes
	// Ex. We want to pass vertices to location 0 (specified in the vertex shader).
	// Describe vertex array properties through parameters
	// Automatically takes data from VBO bound to GL_ARRAY_BUFFER
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(index);

	// Unbind from the VBO.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Object::bufferData(const std::vector<unsigned int>* data, int index) {
	// Indicate intent to use this buffer object for element data (indices)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[index]);

	// Send data to buffer binded to GL_ELEMENT_ARRAY_BUFFER
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data->size(), data->data(), GL_STATIC_DRAW);

	// Don't unbind from the EBO while VAO is active to link EBO with VAO
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}