#include <iostream>
#include <BitEngine/Engine.h>
#include <BitEngine/Keys.h>
#include <BitEngine/KeyInputManager.h>
#include <BitEngine/Window.h>
#include <BitEngine/Renderer.h>
#include <BitEngine/Texture.h>
#include <BitEngine/TaskManager.h>
#include <BitEngine/Time.h>
#include <BitEngine/MouseInputManager.h>
#include <BitEngine/ECS.h>
#include <BitEngine/System.h>
#include <BitEngine/Archetype.h>
#include <string>
#include <SDL2/SDL.h>
#include <queue>

struct Position
{
	float x{ 0.0f };
	float y{ 0.0f };
};

struct CircleTexture
{
	static BE::Texture texture;
};

BE::Texture CircleTexture::texture;

struct CircleRenderSystem final : public BE::System<Position, CircleTexture>
{
	virtual void update(const std::vector<BE::Archetype *> &archtypes) override {}

	virtual void render(const std::vector<BE::Archetype *> &archtypes) override
	{
		for (auto archetype : archtypes)
		{
			Position *positions = archetype->getComponentArray<Position>();

			for (std::size_t i = 0; i < archetype->count(); i++)
			{
				SDL_Rect dstRect{ (int)positions[i].x, (int)positions[i].y, 64, 64 };
				SDL_RenderCopy(BE::Renderer::getInstance(), CircleTexture::texture, nullptr, &dstRect);
			}
		}
	}
};

class Game final : public BE::Engine
{
public:
	Game() = default;
	~Game() = default;

	virtual void initialize() override
	{
		BE::Window::getInstance().setFrameLimit(60);
		BE::Window::getInstance().setTitle("Test Game");

		m_ecs.registerSystem<CircleRenderSystem>();
		CircleTexture::texture.load("resources/circle.png");

		m_ecs.newEntity<Position, CircleTexture>();
	}

	virtual void update() override
	{
		m_ecs.update();
	}

	virtual void render() override
	{
		m_ecs.render();
	}

	virtual void shutdown() override
	{
	}
private:
	BE::ECS m_ecs;
};

int main(int argc, char *argv[])
{
	Game game;
	game.run();

	return 0;
}