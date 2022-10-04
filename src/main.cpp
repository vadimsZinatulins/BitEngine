#include <iostream>

#include "Engine.h"
#include "utils/runAsync.h"

class Game : public be::Engine {
public:
	Game() = default;
	~Game() = default;
private:
	void onInitialize() override {
		be::utils::runAsync([] { std::cout << "onInitialize()" << std::endl; })->result();
	}

	void onShutdown() override {
		be::utils::runAsync([] { std::cout << "onShutdown()" << std::endl; })->result();
	}
};

int main(int argc, char *argv[]) {
	Game game;
	game.run();

	return 0;
}
