#pragma once

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "ShaderFile.h"

/*
 * This class compiles the given shader code and loads the compiled shader 
 * program into the GPU. It is also the interface for setting shader 
 * uniform values.
 */
class Shaders {
private:
	// How many bytes to allocate for error messages from shader compilation
	static const int INFO_LOG_BUFFER_SIZE = 512;

	// Id of compiled shader program
	GLuint programID;

	// Helper function to compile each shader
	GLuint compileShader(GLenum type, ShaderFile file);

public:
	Shaders(ShaderFile vertFile, ShaderFile fragFile);
	~Shaders();

	// Loads the compiled shader program into the GPU
	void load();

	// Functions that find the location of the uniform variables in the 
	// shader program and sets them to the parameter's value.
	// It is up to user to match the name parameter to the names in the shader.
	void setUniformMatrix(const GLchar* name, glm::mat4& matrix);
	void setUniformVec(const GLchar* name, glm::vec3& vector);
};