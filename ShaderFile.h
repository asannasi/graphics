#pragma once

#include <string>
#include <iostream>
#include <fstream>

class ShaderFile {
private:
	std::string shaderCode;

public:
	ShaderFile::ShaderFile(std::string fileName);
	ShaderFile::~ShaderFile();
	const std::string* ShaderFile::getCode();
};