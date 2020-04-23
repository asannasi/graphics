#pragma once

#include <string>
#include <iostream>
#include <fstream>

class ShaderFile {
private:
	std::string shaderCode;

public:
	ShaderFile(std::string fileName);
	~ShaderFile();
	const std::string* getCode();
};