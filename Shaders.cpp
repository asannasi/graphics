#include "Shaders.h"

Shaders::Shaders(std::string vShaderFilename, std::string fShaderFilename) {
	// Attempt compiling shaders for GPU
	GLuint vertexShader;
	GLuint fragmentShader;
	compileShader(vertexShader, GL_VERTEX_SHADER, vShaderFilename);
	compileShader(fragmentShader, GL_FRAGMENT_SHADER, fShaderFilename);

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

	glUseProgram(programID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shaders::compileShader(GLuint& id, GLenum type, std::string filename) {
	// Get ref id for shader object
	id = glCreateShader(type);
	// Parse shader file and compile at runtime
	ShaderFile file = ShaderFile(filename);
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
}

Shaders::~Shaders() {
	glDeleteProgram(programID);
}

void Shaders::setUniformModel(glm::mat4 &model) {
	int modelLoc = glGetUniformLocation(programID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void Shaders::setUniformView(glm::mat4& view) {
	int viewLoc = glGetUniformLocation(programID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void Shaders::setUniformProj(glm::mat4& proj) {
	int projLoc = glGetUniformLocation(programID, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
}