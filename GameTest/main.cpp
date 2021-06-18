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
#include <BitEngine/IScene.h>
#include <BitEngine/SceneManager.h>
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
	virtual void update(const std::vector<BE::ArchetypePtr> &archtypes) override {}

	virtual void render(const std::vector<BE::ArchetypePtr> &archtypes) override
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

struct MainScene final : public BE::IScene
{
	virtual void initialize() override
	{
		ecs.registerSystem<CircleRenderSystem>();
		auto e = ecs.newEntity<Position, CircleTexture>({ 400 - 32, 300 - 32 }, {});
		ecs.getComponent<Position>(e).x = 0;
	}

	virtual void shutdown() override
	{
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

		CircleTexture::texture.load("resources/circle.png");

		BE::SceneManager::getInstance().changeScene<MainScene>();
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