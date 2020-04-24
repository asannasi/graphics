#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>

#include "ObjFile.h"

class Object
{
private:
	const std::vector<glm::vec3>* vertices;
	glm::mat4 modelToWorld;
	GLuint vbo;
	GLuint vao;

public:
	Object(const std::vector<glm::vec3>* vertices);
	~Object();
	int getNumVertices();
	GLuint getVAO();
	void spin(float deg, glm::vec3 axis);
	glm::mat4 getModelMatrix();
};

