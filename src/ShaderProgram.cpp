#include "ShaderProgram.h"

#include <glad/glad.h>
#include <iostream>
#include <vector>

namespace be::graphics {

void ShaderProgram::init() {
	// Make sure that the program hasn't been created yet
	if(!m_id) {
		return;
	}

	// Create the shader program
	m_id = glCreateProgram();
}

void ShaderProgram::clear() {
	// Make sure that the program has been created
	if(m_id) {
		// Delete the program and reset its value
		glDeleteProgram(m_id);
		m_id = 0;
	}
}

void ShaderProgram::attachShader(unsigned int shader) {
	// Make sure that the program has been created
	if(!m_id) {
		return;
	}

	// Attach the shader to the program
	glAttachShader(m_id, shader);
}

void ShaderProgram::use() {
	// Make sure that the program has been created
	if(m_id) {
		glUseProgram(m_id);
	}
}

void ShaderProgram::unuse() {
	glUseProgram(0);
}

void ShaderProgram::linkProgram() {
	// Make sure that the program has been created
	if(!m_id) {
		return;
	}

	// Link the program
	glLinkProgram(m_id);

	// Check if link was successfull
	GLint success;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if(!success) {
		// Get the log size
		GLint size;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &size);

		// Get the log
		std::vector<GLchar> log(size);
		glGetProgramInfoLog(m_id, size, &size, log.data());

		// Print the log
		std::cout << "Failed to link program" << std::endl;
		std::cout << (char*)log.data() << std::endl;
	}
}

}
