#include "VertexShader.h"

#include <glad/glad.h>

namespace be::graphics {

void VertexShader::init(const char *shaderFilePath) {
	load(shaderFilePath, GL_VERTEX_SHADER);
}

void VertexShader::clear() {
	if(m_id) {
		glDeleteShader(m_id);
	}
}

}
