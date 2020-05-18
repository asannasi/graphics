#pragma once

#include <string>
#include <iostream>
#include <fstream>

/*
 * Parses the code in a shader GLSL file into a string.
 */
class ShaderFile {
private:
	// Code in the shader file stored as a string
	std::string code;

public:
	// Create a string from the file contents
	ShaderFile(std::string fileName);

	const std::string* getCode();
};