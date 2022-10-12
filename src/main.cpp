#include <iostream>
#include <vector>

#include "Engine.h"
#include "scene/IScene.h"
#include "scene/SceneManager.h"
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

struct MainMenuScene : public be::scene::IScene {
	void initialize() override {
		m_model.init();
	}

	void shutdown() override {
		m_model.close();
	}

	void update() override {
	
	}

	void render() override {
		m_model.render();
	}

	Model m_model;
};

class Game : public be::Engine {
public:
	Game() = default;
	~Game() = default;
private:
	void onInitialize() override {
		be::scene::SceneManager::getInstance().pushScene<MainMenuScene>();
	}

	void onShutdown() override {
	}
};

int main(int argc, char *argv[]) {
	Game game;
	game.run();

	return 0;
}
