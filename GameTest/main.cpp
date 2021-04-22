#include <iostream>
#include <BitEngine/Engine.h>
#include <BitEngine/utils/CacheSet.h>
#include <BitEngine/Keys.h>

class Game final : public BE::Engine
{
public:
	Game() = default;
	~Game() = default;

	virtual void initialize() override
	{

	}

	virtual void update(float deltaTime) override
	{
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