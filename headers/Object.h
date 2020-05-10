#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>

#include "ObjFile.h"

class Object
{
private:
	// Where translation values are in the model matrix
	static const int TRANSLATION_INDEX = 3;

	static const int NUM_BUFFERS = 3; // Total number of buffer object id's

	// Match the attribute index locations with those defined in the shader
	static const int VERTEX_ATTR_INDEX = 0;
	static const int NORMAL_ATTR_INDEX = 1;
	static const int FACES_ATTR_INDEX = 2;

	const std::vector<glm::vec3>* vertices; // list of vertices
	const std::vector<glm::vec3>* normals; // list of normals
	const std::vector<unsigned int>* faces; // list of faces

	GLuint buffers[NUM_BUFFERS]; // vertex buffer object ids

	glm::mat4 modelToWorld; // changes model coordinates to world space
	GLuint vao; // vertex attribute object id
	bool spinning; // Whether the model should spin

	void bufferData(const std::vector<glm::vec3>* data, int index);
	void bufferData(const std::vector<unsigned int>* data, int index);

public:
	Object(const std::vector<glm::vec3>* v, 
		const std::vector<glm::vec3>* n, 
		const std::vector<unsigned int>* f);
	Object(ObjFile& objFile);
	~Object();

	// Getters and Setters
	GLuint getVAO();
	int getNumVertices();
	int getNumFaces();
	void setSpinning(bool spin);
	bool isSpinning();
	glm::mat4& getModelMatrix();
	GLuint getFacesEBO();

	void update(); // updates model if in moving state

	// rotates model along specified axis by given degrees
	void rotate(float deg, glm::vec3 axis);
	// translates model independent of other transformations
	// and cumatively for past translations
	void translate(GLfloat dist, glm::vec3 axis);

	void uniformScale(GLfloat factor);
};

