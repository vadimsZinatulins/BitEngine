#include "graphics/FragmentShader.h"

#include <glad/glad.h>

namespace be::graphics {

FragmentShader FragmentShader::create(const char *filePath) {
	FragmentShader fs;

	fs.init(filePath);

	return fs;
}


void FragmentShader::init(const char *shaderFilePath) {
	load(shaderFilePath, GL_FRAGMENT_SHADER);
}

void FragmentShader::clear() {
	if(m_id) {
		glDeleteShader(m_id);
	}
}

}
