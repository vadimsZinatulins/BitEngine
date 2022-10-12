#include "input/Keyboard.h"

namespace be::input {

Keyboard &Keyboard::getInstance() {
	static Keyboard instance;
	return instance;
}

bool Keyboard::isKeyPressed(Key key) const { return m_currFrameKeys.contains(key) && !m_oldFrameKeys.contains(key); }
bool Keyboard::isKeyDown(Key key) const { return m_currFrameKeys.contains(key); }
bool Keyboard::isKeyReleased(Key key) const { return !m_currFrameKeys.contains(key) && m_oldFrameKeys.contains(key); }

void Keyboard::update() { m_oldFrameKeys = m_currFrameKeys;	m_oldFrameKeys = m_currFrameKeys; }

void Keyboard::keyPressed(Key key) { m_currFrameKeys.insert(key); }
void Keyboard::keyReleased(Key key) { m_currFrameKeys.remove(key); }

void Keyboard::KeyMap::operator=(const Keyboard::KeyMap &other) {
	m_size = other.m_size;
	for(unsigned char i = 0; i < m_size; ++i) {
		m_keys[i] = other.m_keys[i];
	}
}

void Keyboard::KeyMap::insert(Key key) {
	if(!contains(key) && m_size < Keyboard::KeyMap::ArraySize) {
		m_keys[m_size++] = key;
	}
}

bool Keyboard::KeyMap::contains(Key key) const {
	for(unsigned char i = 0; i < m_size; ++i) {
		if(m_keys[i] == key) {
			return true;
		}
	}

	return false;
}

void Keyboard::KeyMap::remove(Key key) {
	for(unsigned char i = 0; i < m_size; ++i) {
		if(m_keys[i] == key) {
			m_keys[i] = m_keys[--m_size];
			return;
		}
	}
}

}
