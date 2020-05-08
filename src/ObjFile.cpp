#include "../headers/ObjFile.h"

ObjFile::ObjFile(std::string fileName) {
	FILE* pFile = fopen(fileName.c_str(), "r");
	if (!pFile) {
		throw std::exception("Obj file not found");
	}
	parse(pFile);
	fclose(pFile);
}

ObjFile::~ObjFile() { }

void ObjFile::parse(FILE* pFile) {
	float x, y, z;
	float r, g, b;
	int c1, c2;
	unsigned int v1, v2, v3, n1, n2, n3;

	// Parse each line
	while (!feof(pFile)) {
		c1 = fgetc(pFile);
		c2 = fgetc(pFile);
		// Parse vertex
		if (c1 == 'v' && c2 == ' ') {
			fscanf(pFile, "%f %f %f %f %f %f\n", &x, &y, &z, &r, &g, &b);
			vertices.push_back(glm::vec3(x, y, z));
			colors.push_back(glm::vec3(r, g, b));
		}
		// Parse vertex normal
		else if (c1 == 'v' && c2 == 'n') {
			fscanf(pFile, " %f %f %f\n", &x, &y, &z);
			glm::vec3 normal = glm::vec3(x, y, z);
			normal = (glm::normalize(normal) * 0.5f) + glm::vec3(0.5f, 0.5f, 0.5f);
			normals.push_back(normal);
		}
		// Parse face (3 vertices that define a triangle)
		else if (c1 == 'f' && c2 == ' ') {
			fscanf(pFile, "%u//%u %u//%u %u//%u\n", &v1, &n1, &v2, &n2, &v3, &n3);
			// Subtract 1 because obj file is 1-indexed not 0-indexed
			faces.push_back(v1-1);
			faces.push_back(v2-1);
			faces.push_back(v3-1);
		}
		else {
			// Skip empty lines or comments
			fscanf(pFile, "\n");
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