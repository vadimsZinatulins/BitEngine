#pragma once

#include "IShader.h"

namespace be::graphics {

struct VertexShader : public IShader {
	VertexShader() = default;
	~VertexShader() = default;

	void init(const char *shaderFilePath) override;
	void clear() override;
};

}
