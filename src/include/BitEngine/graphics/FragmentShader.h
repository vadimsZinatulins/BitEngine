#pragma once

#include "IShader.h"

namespace be::graphics {

struct FragmentShader : public IShader {
	FragmentShader() = default;
	~FragmentShader() = default;

	void init(const char *shaderFilePath) override;
	void clear() override;
};

}
