#include "../headers/Shaders.h"

Shaders::Shaders(ShaderFile vertFile, ShaderFile fragFile) {
	// Attempt compiling shaders for GPU
	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertFile);
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragFile);

	// Link compiled shaders into shader program object and activate it
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	// If compilation failed, throw exception and print compile errors
	int linkSuccess;
	char infoLogBuffer[INFO_LOG_BUFFER_SIZE];
	glGetProgramiv(programID, GL_LINK_STATUS, &linkSuccess);
	if (!linkSuccess) {
		glGetProgramInfoLog(programID, INFO_LOG_BUFFER_SIZE, NULL, infoLogBuffer);
		std::cerr << infoLogBuffer << std::endl;
		throw std::exception("Shader not linked. Check cerr.");
	}

	// Individual shaders are no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shaders::~Shaders() {
	glDeleteProgram(programID);
}

GLuint Shaders::compileShader(GLenum type, ShaderFile file) {
	GLuint id = glCreateShader(type);
	const char* code = file.getCode()->c_str();
	glShaderSource(id, 1, &code, NULL);
	glCompileShader(id);

	// If compilation failed, throw exception and print compile errors
	int compileSuccess;
	char infoLogBuffer[INFO_LOG_BUFFER_SIZE];
	glGetShaderiv(id, GL_COMPILE_STATUS, &compileSuccess);
	if (!compileSuccess) {
		glGetShaderInfoLog(id, INFO_LOG_BUFFER_SIZE, NULL, infoLogBuffer);
		std::cerr << infoLogBuffer << std::endl;
		throw std::exception("Shader not compiled. Check cerr.");
	}

	return id;
}

void Shaders::load() {
	glUseProgram(programID);
}

void Shaders::setUniformMatrix(const GLchar* name, glm::mat4& matrix) {
	int location = glGetUniformLocation(programID, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shaders::setUniformVec(const GLchar* name, glm::vec3& vector) {
	int location = glGetUniformLocation(programID, name);
	glUniform3fv(location, 1, glm::value_ptr(vector));
}