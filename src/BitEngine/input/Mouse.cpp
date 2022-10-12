#include "input/Mouse.h"

namespace be::input {

Mouse &Mouse::getInstance() {
	static Mouse instance;
	return instance;
}

bool Mouse::isButtonPressed(MouseButton btn) const {
	char btnMask = (1 << (static_cast<char>(btn) - 1));
	return !((btnMask << 4) & m_buttonState) && (btnMask & m_buttonState);
}

bool Mouse::isButtonDown(MouseButton btn) const {
	char btnMask = (1 << (static_cast<char>(btn) - 1));
	return (btnMask & m_buttonState);
}

bool Mouse::isButtonReleased(MouseButton btn) const {
	char btnMask = (1 << (static_cast<char>(btn) - 1));
	return ((btnMask << 4) & m_buttonState) && !(btnMask & m_buttonState);
}

void Mouse::update() {
	char currFrameMask = m_buttonState & 0x0f;
	m_buttonState = (currFrameMask << 4) | currFrameMask;
	m_dx = m_dy = 0;
}

void Mouse::buttonPressed(MouseButton btn) {
	m_buttonState = (1 << (static_cast<char>(btn) - 1)) | m_buttonState;
}

void Mouse::buttonReleased(MouseButton btn) {
	m_buttonState = ((1 << (static_cast<char>(btn) - 1)) ^ 0xff) & m_buttonState;
}

void Mouse::mouseMoved(int x, int y, int dx, int dy) {
	m_x = x;
	m_y = y;
	m_dx = dx;
	m_dy = dy;
}

}
