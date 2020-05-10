#include "../headers/ObjFile.h"

ObjFile::ObjFile(std::string fileName) {
	FILE* pFile;
	if (fopen_s(&pFile, fileName.c_str(), "r")) {
		throw std::exception("Obj file not found");
	}
	parse(pFile);
	fclose(pFile);
}

ObjFile::~ObjFile() { }

void ObjFile::parse(FILE* pFile) {
	int c1, c2;
	float x, y, z;
	float r, g, b;
	unsigned int v1, v2, v3;
	unsigned int n1, n2, n3;

	// Parse each line
	while (!feof(pFile)) {
		c1 = fgetc(pFile);
		c2 = fgetc(pFile);
		// Parse vertex
		if (c1 == 'v' && c2 == ' ') {
			fscanf_s(pFile, "%f %f %f %f %f %f\n", &x, &y, &z, &r, &g, &b);
			vertices.push_back(glm::vec3(x, y, z));

			maxX = glm::max(x, maxX);
			maxY = glm::max(y, maxY);
			maxZ = glm::max(z, maxZ);

			minX = glm::min(x, minX);
			minY = glm::min(y, minY);
			minZ = glm::min(z, minZ);

			colors.push_back(glm::vec3(r, g, b));
		}
		// Parse vertex normal
		else if (c1 == 'v' && c2 == 'n') {
			fscanf_s(pFile, " %f %f %f\n", &x, &y, &z);
			glm::vec3 normal = glm::vec3(x, y, z);
			normal = (glm::normalize(normal) * 0.5f) + glm::vec3(0.5f, 0.5f, 0.5f);
			normals.push_back(normal);
		}
		// Parse face (3 vertices that define a triangle)
		else if (c1 == 'f' && c2 == ' ') {
			fscanf_s(pFile, "%u//%u %u//%u %u//%u\n", &v1, &n1, &v2, &n2, &v3, &n3);
			// Subtract 1 because obj file is 1-indexed not 0-indexed
			faces.push_back(v1-1);
			faces.push_back(v2-1);
			faces.push_back(v3-1);
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

void ObjFile::normalize() {
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i][0] = (2 * (vertices[i][0] - minX) / (maxX - minX) ) - 1;
		vertices[i][1] = (2 * (vertices[i][1] - minY) / (maxY - minY) ) - 1;
		vertices[i][2] = (2 * (vertices[i][2] - minZ) / (maxZ - minZ) ) - 1;
	}
}