#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>

class Cube {
private:
	std::vector<glm::vec3> vertices;

	glm::mat4 modelToWorld = glm::mat4(1.0f);

	GLuint vao;
	GLuint vbo;

public:
	Cube(float length);
	~Cube();

	const std::vector<glm::vec3>* Cube::getVertices();
	glm::mat4& getModelMatrix();

	void draw();
};

