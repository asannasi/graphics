#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>

class ObjFile {
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;

	// helper function to parse lines in obj file
	void parse(FILE* pFile);

public:
	// constructor opens file and parses it
	ObjFile(std::string fileName);
	~ObjFile();
	
	// Returns a pointer to the vertices parsed in the object file
	const std::vector<glm::vec3>* getVertices();
	const std::vector<glm::vec3>* getNormals();
};