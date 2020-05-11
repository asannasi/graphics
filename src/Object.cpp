#include "../headers/Object.h"

Object::Object(ObjFile& objFile){
	// Translate the model so the center is at the origin
	//translate((objFile.minVertX + objFile.maxVertX) / 2, glm::vec3(1, 0, 0));
	//translate((objFile.minVertY + objFile.maxVertY) / 2, glm::vec3(0, 1, 0));
	//translate((objFile.minVertZ + objFile.maxVertZ) / 2, glm::vec3(0, 0, 1));
	
	// Scale the model so it fits in a 2x2 cube
	/*
	glm::vec3 scaleFactor = glm::vec3(
		1 / glm::max(abs(objFile.maxX), abs(objFile.minX)), 
		1 / glm::max(abs(objFile.maxY), abs(objFile.minY)), 
		1 / glm::max(abs(objFile.maxZ), abs(objFile.minZ))
	);
	modelToWorld = glm::scale(modelToWorld, scaleFactor);
	*/

	objFile.normalize();

	// To store vertex attribute pointer configurations, use vertex array object (VAO)
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Allocate buffer objects that will store data in GPU memory
	glGenBuffers(NUM_BUFFERS, buffers);
	vertices = objFile.getVertices();
	bufferData(vertices, VERTEX_ATTR_INDEX);
	normals = objFile.getNormals();
	bufferData(normals, NORMAL_ATTR_INDEX);
	faces = objFile.getFaces();
	bufferData(faces, FACES_ATTR_INDEX);

	// Unbind from the VAO.
	glBindVertexArray(0);
}

Object::~Object(){
	glDeleteBuffers(NUM_BUFFERS, buffers);
	glDeleteVertexArrays(1, &vao);
}

void Object::bufferData(const std::vector<glm::vec3>* data, int index) {
	// Indicate intent to use this buffer object for attribute data
	glBindBuffer(GL_ARRAY_BUFFER, buffers[index]);

	// Send data to buffer binded to GL_ARRAY_BUFFER.
	// Uses GL_STATIC_DRAW since data won't be changed, only the model matrix.
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * data->size(), data->data(), GL_STATIC_DRAW);

	// Tell openGL how to interpret data in memory by communicating with the
	// shader through attributes.
	// Ex. We want to pass vertices to location 0 (specified in the vertex shader).
	// Describe vertex array properties through parameters.
	// Automatically takes data from VBO bound to GL_ARRAY_BUFFER.
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
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::rotate(float deg, glm::vec3 axis) {
	// Update the model matrix by multiplying a rotation matrix
	modelToWorld = glm::rotate(modelToWorld, glm::radians(deg), axis);
}

glm::mat4& Object::getModelMatrix() {
	return modelToWorld;
}

bool Object::isSpinning() {
	return spinning;
}

void Object::setSpinning(bool spinning) {
	this->spinning = spinning;
}

void Object::setDrawModePointCloud() {
	drawMode = DrawMode::POINTCLOUD;
}

void Object::setDrawModeMesh() {
	drawMode = DrawMode::MESH;
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

void Object::update() {
	if (spinning) {
		rotate(0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
}

void Object::draw() {
	glBindVertexArray(vao);
	if (drawMode == DrawMode::POINTCLOUD) {
		glDrawArrays(GL_POINTS, 0, vertices->size());
	}
	else {
		glDrawElements(GL_TRIANGLES, faces->size(), GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0); // Unbind VAO
}