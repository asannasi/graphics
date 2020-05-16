#include "../headers/Cube.h"

Cube::Cube(float length, glm::vec3 color) : color(color) {
	vertices.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	vertices.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	vertices.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	vertices.push_back(glm::vec3(1.0f, 1.0f, -1.0f));

	// Create vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Allocate buffer objects that will store data in GPU memory
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	
	// Set location 0 to vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Cube::~Cube() {
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void Cube::draw() {
	glBindVertexArray(vao);
	glPointSize(10.0f);
	glDrawArrays(GL_POINTS, 0, vertices.size());
	glBindVertexArray(0);
	glPointSize(1.0f);
}