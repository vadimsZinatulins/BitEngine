#pragma once 

namespace be {

class Engine;

}

namespace be::input {

enum class MouseButton:char { Left = 1, Middle = 2, Right = 3 };

class Mouse {
public:
	static Mouse &getInstance();

	bool isButtonPressed(MouseButton btn) const;
	bool isButtonDown(MouseButton btn) const;
	bool isButtonReleased(MouseButton btn) const;
	
	void getMouseCoords(int &x, int &y) const;
	void getMouseRelCoords(int &dx, int &dy) const;
private:
	friend class be::Engine;

	Mouse() = default;
	~Mouse() = default;

	void update();
	
	void buttonPressed(MouseButton btn);
	void buttonReleased(MouseButton btn);
	
	void mouseMoved(int x, int y, int dx, int dy);
	
	int m_scroll { 0 };
	
	int m_x { 0 };
	int m_y { 0 };
	
	int m_dx { 0 };
	int m_dy { 0 };
	
	char m_buttonState { 0 };
};

}
