#include <iostream>
#include <BitEngine/Engine.h>
#include <BitEngine/Keys.h>
#include <BitEngine/KeyInputManager.h>
#include <BitEngine/Window.h>

class Game final : public BE::Engine
{
public:
	Game() = default;
	~Game() = default;

	virtual void initialize() override
	{
		BE::Window::getInstance().setFrameLimit(60);
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
	}

	virtual void shutdown() override
	{
	}
private:
};

int main(int argc, char *argv[])
{
	Game game;
	game.run();

	return 0;
}