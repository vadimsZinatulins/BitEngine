#include <iostream>
#include <BitEngine/Engine.h>
#include <BitEngine/Keys.h>
#include <BitEngine/KeyInputManager.h>
#include <BitEngine/Window.h>
#include <BitEngine/Renderer.h>
#include <BitEngine/Texture.h>
#include <BitEngine/TaskManager.h>
#include <string>
#include <SDL2/SDL.h>

class Game final : public BE::Engine
{
public:
	Game() = default;
	~Game() = default;

	virtual void initialize() override
	{
		BE::Window::getInstance().setFrameLimit(60);

		m_texture.load("resources/circle.png");

		auto t1 = BE::make_task([] { return 4; });
		auto t2 = BE::make_task([] { return 6; });
		BE::make_task([](int x, int y) { std::cout << (x + y) << std::endl; return 0; }, t1, t2);
	}

	virtual void update() override
	{
		if (BE::KeyInputManager::getInstance().isKeyReleased(BE::Key::KEY_SPACE))
		{
			std::cout << "Key pressed" << std::endl;
		}
	}

	virtual void render() override
	{
		SDL_RenderCopy(BE::Renderer::getInstance(), m_texture, nullptr, nullptr);
	}

	virtual void shutdown() override
	{
	}
private:
	BE::Texture m_texture;
};

int main(int argc, char *argv[])
{
	Game game;
	game.run();

	return 0;
}