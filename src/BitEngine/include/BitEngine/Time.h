#pragma once

namespace be {

class Time {
public:
	static inline unsigned int getTicks();
	static inline float getDeltaTime();
private:
	friend class Engine;

	Time();
	~Time();

	static unsigned int m_ticks;
	static float m_deltaTime;
};

// using getDeltaTime = Time::getDeltaTime;
// using getTicks = Time::getTicks;

}
