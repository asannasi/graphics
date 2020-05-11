#pragma once

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderFile.h"

/*
 * This class compiles the given shader code and loads the compiled shader 
 * program into the GPU. It is also the interface for setting shader 
 * uniform values.
 */
class Shaders
{
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

	// Functions that find the location of the uniform matrices in the 
	// shader program and sets them to the parameter's value.
	void setUniformModel(glm::mat4& model);
	void setUniformView(glm::mat4& view);
	void setUniformProj(glm::mat4& proj);
	void setUniformProjView(glm::mat4 ProjView);
};