#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <limits>

class ObjFile {
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> faces;

	// helper function to parse lines in obj file
	void parse(FILE* pFile);

public:
	// constructor opens file and parses it
	ObjFile(std::string fileName);
	~ObjFile();
	
	void normalize();

	// Returns a pointer to data parsed in the object file
	const std::vector<glm::vec3>* getVertices();
	const std::vector<glm::vec3>* getColors();
	const std::vector<glm::vec3>* getNormals();
	const std::vector<unsigned int>* getFaces();

	// Max vertex values for normalizing
	float maxX = std::numeric_limits<float>::min();
	float maxY = std::numeric_limits<float>::min();
	float maxZ = std::numeric_limits<float>::min();

	float minX = std::numeric_limits<float>::max();
	float minY = std::numeric_limits<float>::max();
	float minZ = std::numeric_limits<float>::max();
};