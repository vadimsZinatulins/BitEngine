#include <iostream>

#include "Engine.h"

class Game : public be::Engine {
public:
	Game() = default;
	~Game() = default;
private:
	void onInitialize() override {
	
	}

	void onShutdown() override {
	
	}
};

int main(int argc, char *argv[]) {
	Game game;
	game.run();

	return 0;
}
