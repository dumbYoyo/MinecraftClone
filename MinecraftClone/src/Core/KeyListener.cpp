#include "KeyListener.h"

KeyListener* KeyListener::m_instance = nullptr;

KeyListener::KeyListener() {  }

KeyListener* KeyListener::Get()
{
	if (m_instance == nullptr)
		m_instance = new KeyListener();
	return m_instance;
}

void KeyListener::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		Get()->m_keyPressed[key] = true;
		Get()->m_keyClicked[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		Get()->m_keyPressed[key] = false;
		Get()->m_keyClicked[key] = false;
	}
}

void KeyListener::EndFrame()
{
	for (int i = 0; i < sizeof(Get()->m_keyClicked) / sizeof(bool); i++)
	{
		Get()->m_keyClicked[i] = false;
	}
}

bool KeyListener::GetKeyPressed(int key)
{
	return Get()->m_keyPressed[key];
}

bool KeyListener::GetKeyClicked(int key)
{
	return Get()->m_keyClicked[key];
}
