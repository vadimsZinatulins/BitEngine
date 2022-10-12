#include "graphics/IShader.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <glad/glad.h>

namespace be::graphics {

IShader::operator unsigned int() const {
	return m_id;
}

void IShader::load(const char *path, int type) {
	// Make sure that shader hasn't been loaded yet
	if(m_id) {
		return;
	}

	// Buffer which will contain file data
	std::stringstream buffer;

	{
		// Open the the and make sure it was opened successfully
		std::ifstream shaderFile { path };
		if(shaderFile.fail()) {
			std::cout << "Failed to open shader file at: " << path << std::endl;
			return;
		}

		// Read file content
		buffer << shaderFile.rdbuf();
	}

	// Convert file data to GLchar pointer
	std::string content { buffer.str() } ;
	GLchar *source { (GLchar*)content.c_str() };

	// Create shader
	m_id = glCreateShader(type);

	// Attach file content to the shader
	glShaderSource(m_id, 1, &source, nullptr);
	// Compile the shader
	glCompileShader(m_id);

	// Retrieve compilation status
	GLint success;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
	// If the compilation fails retrieve the error message and print it
	if(!success) {
		// Retrieve the error message size
		GLint size;
		glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &size);

		// Retrieve the error message
		std::vector<GLchar> log(size);
		glGetShaderInfoLog(m_id, size, &size, log.data());

		// Delete the shader
		glDeleteShader(m_id);

		// Print the error
		std::cout << "Failed to compile shader: " << path << std::endl;
		std::cout << (char*)log.data() << path << std::endl;
	}
}

}
