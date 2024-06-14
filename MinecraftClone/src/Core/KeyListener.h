#pragma once

#include <GLFW/glfw3.h>

class KeyListener
{
public:
	KeyListener(const KeyListener& keyboardListener) = delete;

	static KeyListener* Get();
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void EndFrame();
	static bool GetKeyPressed(int key);
	static bool GetKeyClicked(int key);

private:
	KeyListener();

	static KeyListener* m_instance;
	bool m_keyPressed[350] = { false };
	bool m_keyClicked[350] = { false };
};