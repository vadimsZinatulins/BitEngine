#pragma once 

namespace be::graphics {

class ShaderProgram {
public:
	ShaderProgram() = default;
	~ShaderProgram() = default;

	static ShaderProgram create(auto ...shaders) {
		ShaderProgram program;

		program.init();
		(..., program.attachShader(shaders));
		program.linkProgram();

		return program;
	}

	void init();
	void clear();

	void attachShader(unsigned int shader);
	void linkProgram();

	void use();
	void unuse();
private:
	unsigned int m_id { 0 };
};

}
