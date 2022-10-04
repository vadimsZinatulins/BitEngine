#include <iostream>
#include <vector>

#include "Engine.h"
#include "utils/runAsync.h"
#include "graphics/VertexShader.h"
#include "graphics/FragmentShader.h"
#include "graphics/ShaderProgram.h"
#include "graphics/VertexArrayObject.h"

class Model {
public:
	Model() = default;
	~Model() = default;

	void init() {
		auto vs = be::graphics::VertexShader::create("shaders/vs.glsl");
		auto fs = be::graphics::FragmentShader::create("shaders/fs.glsl");

		m_program = be::graphics::ShaderProgram::create(vs, fs);

		vs.clear();
		fs.clear();

		m_vao = be::graphics::VertexArrayObject::create();

		std::vector<float> positions {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		m_vao.addAttribute(positions, 3);
	}

	void close() {
		m_vao.clear();
		m_program.clear();
	}

	void render() {
		m_program.use();
		m_vao.enable();

		m_vao.draw();

		m_vao.disable();
		m_program.unuse();
	}
private:
	be::graphics::VertexArrayObject m_vao;
	be::graphics::ShaderProgram m_program;
};

class Game : public be::Engine {
public:
	Game() = default;
	~Game() = default;
private:
	void onInitialize() override {
		m_model.init();
	}

	void onShutdown() override {
		m_model.close();
	}

	void render() override {
		m_model.render();
	}

	Model m_model;
};

int main(int argc, char *argv[]) {
	Game game;
	game.run();

	return 0;
}
