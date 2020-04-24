#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>

#include "ObjFile.h"

class Object
{
private:
	const int TRANSLATION_INDEX = 3;
	const std::vector<glm::vec3>* vertices; // list of vertices
	glm::mat4 modelToWorld; // changes model coordinates to world space
	GLuint vbo; // vertex buffer object id
	GLuint vao; // vertex attribute object id
	bool spinning; // Whether the model should spin

public:
	Object(const std::vector<glm::vec3>* vertices);
	~Object();

	// Getters and Setters
	GLuint getVAO();
	int getNumVertices();
	void setSpinning(bool spin);
	bool isSpinning();
	glm::mat4& getModelMatrix();

	void update(); // updates model if in moving state

	// rotates model along specified axis by given degrees
	void rotate(float deg, glm::vec3 axis);
	// translates model independent of other transformations
	// and cumatively for past translations
	void translate(GLfloat dist, glm::vec3 axis);

};

