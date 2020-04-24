#include "ShaderFile.h"

ShaderFile::ShaderFile(std::string fileName) {
	std::ifstream fStream(fileName, std::ios::in);
	if (!fStream.is_open()) {
		throw std::exception("Shader file not found");
	}
	while (fStream.is_open() && fStream.good()){
		std::string line = "";
		getline(fStream, line);
		shaderCode += "\n" + line;
	}
	fStream.close();
}

ShaderFile::~ShaderFile() { }

const std::string* ShaderFile::getCode() {
	return &shaderCode;
}