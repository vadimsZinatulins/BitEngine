#include "KeyInputManager.h"

namespace BE
{

KeyInputManager KeyInputManager::m_instance;

KeyInputManager &KeyInputManager::getInstance()
{
	return m_instance;
}

bool KeyInputManager::isKeyPressed(Key key)
{
}

bool KeyInputManager::isKeyDown(Key key)
{
	return false;
}

bool KeyInputManager::isKeyReleased(Key key)
{
	return false;
}

void KeyInputManager::keyPressed(Key key)
{
}

void KeyInputManager::keyReleased(Key key)
{
}

void KeyInputManager::update()
{
}

}