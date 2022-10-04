#include "FragmentShader.h"

#include <glad/glad.h>

namespace be::graphics {

void FragmentShader::init(const char *shaderFilePath) {
	load(shaderFilePath, GL_FRAGMENT_SHADER);
}

void FragmentShader::clear() {
	if(m_id) {
		glDeleteShader(m_id);
	}
}

}
