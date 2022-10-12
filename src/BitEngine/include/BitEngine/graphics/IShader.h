#pragma once

namespace be::graphics {

class IShader {
public:
	IShader() = default;
	virtual ~IShader() = default;

	virtual void init(const char *shaderFilePath) = 0;
	virtual void clear() = 0;

	operator unsigned int() const;
protected:
	void load(const char *path, int type);
	unsigned int m_id { 0 };
};

}
