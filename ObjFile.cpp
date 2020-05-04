#include "ObjFile.h"

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

	while (!feof(pFile)) {
		c1 = fgetc(pFile);
		c2 = fgetc(pFile);

		if (c1 == 'v' && c2 == ' ') {
			fscanf(pFile, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
			vertices.push_back(glm::vec3(x, y, z));
		}
		else if (c1 == 'v' && c2 == 'n') {
			fscanf(pFile, " %f %f %f", &x, &y, &z);
			glm::vec3 normal = glm::vec3(x, y, z);
			normal = (glm::normalize(normal) * 0.5f) + glm::vec3(0.5f, 0.5f, 0.5f);
			normals.push_back(normal);
		}
	}
}

const std::vector<glm::vec3>* ObjFile::getVertices() {
	return &vertices;
}

const std::vector<glm::vec3>* ObjFile::getNormals() {
	return &normals;
}