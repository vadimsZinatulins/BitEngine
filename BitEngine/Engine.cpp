#include "Engine.h"

#include <SDL2/SDL.h>

namespace BE
{

void Engine::run()
{
	init();
	loop();
	quit();
}

void Engine::init()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
}

void Engine::loop()
{
	SDL_Event e;
	bool isRunning = true;
	while (isRunning)
	{
		// Process all SDL events
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			}
		}


	}
}

void Engine::quit()
{
	// Shutdown SDL
	SDL_Quit();
}

}