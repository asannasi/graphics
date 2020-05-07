#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

class Object
{
private:
	// Where translation values are in the model matrix
	static const int TRANSLATION_INDEX = 3;

	// Match the attribute index locations with those defined in the shader
	static const int VERTEX_ATTR_INDEX = 0;
	static const int NORMAL_ATTR_INDEX = 1;

	const std::vector<glm::vec3>* vertices; // list of vertices
	const std::vector<glm::vec3>* normals; // list of normals

	int numBuffers; // Total number of buffer object id's
	GLuint* buffers; // vertex buffer object ids

	glm::mat4 modelToWorld; // changes model coordinates to world space
	GLuint vao; // vertex attribute object id
	bool spinning; // Whether the model should spin

	void bufferData(const std::vector<glm::vec3>* data, int index);

public:
	Object(const std::vector<glm::vec3>* v);
	Object(const std::vector<glm::vec3>* v, const std::vector<glm::vec3>* n);
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

	void uniformScale(GLfloat factor);

};

