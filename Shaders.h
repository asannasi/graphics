#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "ShaderFile.h"

class Shaders
{
private:
	GLuint programID;
	static const int INFO_LOG_BUFFER_SIZE = 512;

	void compileShader(GLuint& id, GLenum type, std::string filename);
public:
	Shaders() = default;
	Shaders(std::string vShaderFilename, std::string fShaderFilename);
	~Shaders();

	void setUniformModel(glm::mat4& model);

	void setUniformView(glm::mat4& view);

	void setUniformProj(glm::mat4& proj);

};

