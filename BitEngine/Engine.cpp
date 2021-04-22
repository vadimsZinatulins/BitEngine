#include "Engine.h"
#include "Window.h"
#include "Renderer.h"

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

	Window::getInstance().open();
}

void Engine::loop()
{
	Window &window = Window::getInstance();
	Renderer &renderer = Renderer::getInstance();

	Uint32 currentFrame = SDL_GetTicks();
	Uint32 previousFrame = currentFrame;

	float accumulated = 0.0f;

	initialize();

	SDL_Event e;
	bool isRunning = true;
	while (isRunning)
	{
		currentFrame = SDL_GetTicks();
		accumulated += (float)(currentFrame - previousFrame) / 1000.0f;
		previousFrame = currentFrame;

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

		while (accumulated >= window.m_deltaTime)
		{
			update(window.m_deltaTime);
			accumulated -= window.m_deltaTime;
		}

		SDL_RenderClear(renderer);

		render();

		SDL_RenderPresent(renderer);
	}

	shutdown();
}

void Engine::quit()
{
	Window::getInstance().close();

	// Shutdown SDL
	SDL_Quit();
}

}