#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <limits>

/*
 * Represents a OBJ file. It parses the file and stores the data in
 * vectors, along with max and min values calculated along the way.
 * To avoid copying large amounts of data, the user should use pointers
 * to the parsed data and not delete the class instance.
 */
 /*
   Sample OBJ File
   v 0.1 0 -1.4 0.93 1 0
   vn -1.4 0.4 0.2
   f 3//3 1//1 4//4
  */
class ObjFile {
private:
	// Vectors to store parsed data
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> faces;

	// Max vertex values for normalizing
	float maxVertX = std::numeric_limits<float>::min();
	float maxVertY = std::numeric_limits<float>::min();
	float maxVertZ = std::numeric_limits<float>::min();

	// Min vertex values for normaliz
	float minVertX = std::numeric_limits<float>::max();
	float minVertY = std::numeric_limits<float>::max();
	float minVertZ = std::numeric_limits<float>::max();

	// Helper functions to parse lines in OBJ file
	void parse(FILE* pFile);
	void parseVertexLine(FILE* pFile); // Also recomputes max and min
	void parseNormalLine(FILE* pFile); // Also normalizes values [-1,1] into [0,1]
	void parseFaceLine(FILE* pFile);

public:
	// Standard default constructor to allow stack allocation
	ObjFile() = default;

	// This constructor will open the file and parse it. 
	// Exceptions may be thrown.
	ObjFile(std::string fileName);

	~ObjFile();

	// Returns a pointer to data parsed from the OBJ file
	const std::vector<glm::vec3>* getVertices();
	const std::vector<glm::vec3>* getColors();
	const std::vector<glm::vec3>* getNormals();
	const std::vector<unsigned int>* getFaces();
	
	// Normalizes vertices into a range of [-1,1]
	void normalize();
};