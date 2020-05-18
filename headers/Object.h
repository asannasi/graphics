#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>

#include "ObjFile.h"

class Object {
private:
	static const int AVG_DIVISOR = 2;

	// Where translation values reside in the model matrix
	static const int TRANSLATION_INDEX = 3;

	// Number of elements in glm::vec3
	static const int NUM_DIM = 3;

	// Matches the attribute index locations with those defined in the shader
	static const int VERTEX_ATTR_INDEX = 0;
	static const int NORMAL_ATTR_INDEX = 1;
	static const int FACES_ATTR_INDEX = 2;

	const std::vector<glm::vec3>* vertices;
	const std::vector<glm::vec3>* normals;
	const std::vector<unsigned int>* faces;

	glm::vec3 color;

	// Object States
	//
	glm::mat4 modelToWorld = glm::mat4(1.0f); // Where model is in world space
	bool spinning = false;
	enum class DrawMode { POINTCLOUD, MESH } drawMode = DrawMode::MESH;

	// Vertex attribute object ID. 
	// The VAO stores the state for the Object like buffers and 
	// how to interpret the data stored in them.
	GLuint vao;

	// Buffer object ID's.
	// Includes both vertex and element buffers.
	static const int NUM_BUFFERS = 3;
	GLuint buffers[NUM_BUFFERS];

	// Helper methods for buffering data into vertex and element buffers
	void bufferData(const std::vector<glm::vec3>* data, int index);
	void bufferData(const std::vector<unsigned int>* data, int index);

public:
	Object() = default;
	Object(ObjFile& objFile, glm::vec3 color);
	~Object();

	glm::mat4& getModelMatrix();
	glm::vec3& getColor();

	bool isSpinning();
	void setSpinning(bool spinning);

	void setDrawModePointCloud();
	void setDrawModeMesh();

	// Translates model independent of other transformations
	// and cumalatively with past translations.
	void translate(GLfloat dist, glm::vec3 axis);

	// Scales model cumalatively with past transformations
	void uniformScale(GLfloat factor);

	// Rotates model along specified axis by given degrees
	void rotate(float deg, glm::vec3 axis);

	// Updates object for next frame
	void update(); 

	// Draws model on the screen
	void draw(); 

};

