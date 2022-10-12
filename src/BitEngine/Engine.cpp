#include "Engine.h"
#include "Time.h"
#include "scene/IScene.h"
#include "scene/SceneManager.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <SimpleTaskManager/Scheduler.h>
#include <glad/glad.h>

SDL_Window *m_window { nullptr };
SDL_GLContext m_context { nullptr };

const auto WIDHT { 640 };
const auto HEIGHT { 480 };

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

	m_window = SDL_CreateWindow("BitEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDHT, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	m_context = SDL_GL_CreateContext(m_window);

	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

	glViewport(0, 0, WIDHT, HEIGHT);
	glClearColor(0.23f, 0.65f, 0.15f, 1.0f);

	// Initialize SimpleTaskManager
	stm::Scheduler::getInstance().initialize();

	onInitialize();

	scene::SceneManager::getInstance().updateState();
}

void Engine::loop() {
	SDL_Event e;
	auto isRunning { true };
	auto &keyboard { input::Keyboard::getInstance() };
	auto &mouse { input::Mouse::getInstance() };

	while(scene::IScene *scene = scene::SceneManager::getInstance().getActiveScene()) {
		Time frameTime;

		keyboard.update();
		mouse.update();

		while(SDL_PollEvent(&e)) {
			switch(e.type) {
			case SDL_QUIT:
				scene::SceneManager().getInstance().popAllScenes();
				break;
			case SDL_KEYDOWN:
				keyboard.keyPressed(e.key.keysym.sym);
				break;
			case SDL_KEYUP:
				keyboard.keyReleased(e.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse.buttonPressed(static_cast<input::MouseButton>(e.button.button));
				break;				
			case SDL_MOUSEBUTTONUP:
				mouse.buttonReleased(static_cast<input::MouseButton>(e.button.button));
				break;				
			case SDL_MOUSEMOTION:
				mouse.mouseMoved(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
				break;				
			}
		}

		scene->update();

		glClear(GL_COLOR_BUFFER_BIT);
		scene->render();
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
