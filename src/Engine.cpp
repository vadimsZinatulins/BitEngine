#include "Engine.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <SimpleTaskManager/Scheduler.h>

SDL_Window *m_window { nullptr };
SDL_GLContext m_context { nullptr };

namespace be {

void Engine::run() {
	init();
	loop();
	close();
}

void Engine::init() {
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetSwapInterval(1);

	m_window = SDL_CreateWindow("BitEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	m_context = SDL_GL_CreateContext(m_window);

	// Initialize SimpleTaskManager
	stm::Scheduler::getInstance().initialize();

	onInitialize();
}

void Engine::loop() {
	SDL_Event e;
	bool isRunning { true };

	while(isRunning) {
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			}
		}

		SDL_GL_SwapWindow(m_window);
	}
}

void Engine::close() {
	onShutdown();

	// Shutdown SimpleTaskManager
	stm::Scheduler::getInstance().terminate();

	if(m_context) {
		SDL_GL_DeleteContext(m_context);
		m_context = nullptr;
	}

	if(m_window) {
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}

	// Shutdown SDL
	SDL_Quit();
}

}
