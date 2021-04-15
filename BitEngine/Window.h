#ifndef __BE__WINDOW_H__
#define __BE__WINDOW_H__

#include <string>

namespace BE
{

/*
* Window modes allowed
*/
enum class WindowMode
{
	Windowed = 0,
	Borderless = 1,
	FullScreen = 2,
	Desktop = 3
};

class Window
{
public:
	static Window &getInstance();	// Retrieves the reference to the single instance of Window class

	void setMode(WindowMode mode);
	void setResolution(int width, int height);
	void setTitle(std::string title);
	void setFrameLimit(unsigned int limit);
private:
	friend class Engine;	// Allow Engine class to access private properties

	Window() = default;
	~Window() = default;

	void open();
	void close();

	static Window m_instance;	// Single instance of Window class

	// Current window mode
	WindowMode m_mode{ WindowMode::Windowed };

	// Window resolution
	int m_width{ 800 };
	int m_height{ 600 };

	// Window title
	std::string m_title{ "" };

	// Delta time (probably not the best place to define it)
	float m_deltaTime{ 1.0f / 30.0f };
};

}

#endif // !__BE__WINDOW_H__
