#include "../headers/ObjFile.h"

ObjFile::ObjFile(std::string fileName) {
	FILE* pFile;
	if (fopen_s(&pFile, fileName.c_str(), "r")) {
		throw std::exception("Obj file not found");
	}
	parse(pFile);
	fclose(pFile);
}

void ObjFile::parseVertexLine(FILE* pFile) {
	float x, y, z;
	float r, g, b;
	fscanf_s(pFile, "%f %f %f %f %f %f\n", &x, &y, &z, &r, &g, &b);

	vertices.push_back(glm::vec3(x, y, z));
	colors.push_back(glm::vec3(r, g, b));

	// Update max and min values
	maxVertX = glm::max(x, maxVertX);
	maxVertY = glm::max(y, maxVertY);
	maxVertZ = glm::max(z, maxVertZ);

	minVertX = glm::min(x, minVertX);
	minVertY = glm::min(y, minVertY);
	minVertZ = glm::min(z, minVertZ);
}

void ObjFile::parseNormalLine(FILE* pFile) {
	float x, y, z;
	fscanf_s(pFile, " %f %f %f\n", &x, &y, &z);
	glm::vec3 normal = glm::vec3(x, y, z);

	// Normalize normal vector from [-1, 1] to [0,1] 
	normal = glm::normalize(normal);

	normals.push_back(normal);
}

void ObjFile::parseFaceLine(FILE* pFile) {
	// Parse face (3 vertex and 3 normal indices that define a triangle)
	unsigned int v1, v2, v3;
	unsigned int n1, n2, n3;
	fscanf_s(pFile, "%u//%u %u//%u %u//%u\n", &v1, &n1, &v2, &n2, &v3, &n3);

	// Subtract 1 because OBJ file is 1-indexed not 0-indexed
	faces.push_back(v1 - 1);
	faces.push_back(v2 - 1);
	faces.push_back(v3 - 1);
}

 void ObjFile::parse(FILE* pFile) {
	// Parse each line
	while (!feof(pFile)) {
		// Get first two chars in the current line for line type
		int c1 = fgetc(pFile);
		int c2 = fgetc(pFile);

		if (c1 == 'v' && c2 == ' ') {
			parseVertexLine(pFile);
		}
		else if (c1 == 'v' && c2 == 'n') {
			parseNormalLine(pFile);
		}
		else if (c1 == 'f' && c2 == ' ') {
			parseFaceLine(pFile);
		}
		else {
			// Skip empty lines or comments
			fscanf_s(pFile, "\n");
		}
	}
}

const std::vector<glm::vec3>* ObjFile::getVertices() {
	return &vertices;
}

const std::vector<glm::vec3>* ObjFile::getColors() {
	return &colors;
}

const std::vector<glm::vec3>* ObjFile::getNormals() {
	return &normals;
}

const std::vector<unsigned int>* ObjFile::getFaces() {
	return &faces;
}

glm::vec3 ObjFile::getMaxVertVals() {
	return glm::vec3(maxVertX, maxVertY, maxVertZ);
}

glm::vec3 ObjFile::getMinVertVals() {
	return glm::vec3(minVertX, minVertY, minVertZ);
}

// Normalizes a value to range [-1, 1] using max and min of all values in
// the wanted dimension
float normalizeValue(float value, float max, float min) {
	return ((2 * (value - min) / (max - min)) - 1);
}

void ObjFile::normalize() {
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i][0] = normalizeValue(vertices[i][0], maxVertX, minVertX);
		vertices[i][1] = normalizeValue(vertices[i][1], maxVertY, minVertY);
		vertices[i][2] = normalizeValue(vertices[i][2], maxVertZ, minVertZ);
	}
}