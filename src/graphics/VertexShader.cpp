#include "graphics/VertexShader.h"

#include <glad/glad.h>

namespace be::graphics {

VertexShader VertexShader::create(const char *filePath) {
	VertexShader vs;

	vs.init(filePath);

	return vs;
}

void VertexShader::init(const char *shaderFilePath) {
	load(shaderFilePath, GL_VERTEX_SHADER);
}

void VertexShader::clear() {
	if(m_id) {
		glDeleteShader(m_id);
	}
}

}
