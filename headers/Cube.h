#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>

#include "Object.h"

class Cube : public Object{
private:
	std::vector<glm::vec3> vertices;

	glm::mat4 modelToWorld = glm::mat4(1.0f);

	glm::vec3 color;

	GLuint vao;
	GLuint vbo;

public:
	Cube(float length, glm::vec3 color);
	~Cube();
	void draw();
};

