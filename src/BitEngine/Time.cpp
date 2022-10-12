#include "Time.h"

#include <SDL2/SDL.h>

namespace be {

constexpr unsigned int MinTicksPerFrame = 1000 / 60;

unsigned int Time::m_ticks = 0;
float Time::m_deltaTime = 0.0f;

Time::Time() {
	unsigned int ticks = SDL_GetTicks();
	m_deltaTime = (float)(ticks - m_ticks) / 1000.0f;
	m_ticks = ticks;
}

Time::~Time() {
	unsigned int frameTicks = SDL_GetTicks() - m_ticks;
	if(frameTicks < MinTicksPerFrame) {
		SDL_Delay(MinTicksPerFrame - frameTicks);
	}
}

}
