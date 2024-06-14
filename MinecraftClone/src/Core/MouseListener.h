#pragma once

#include <GLFW/glfw3.h>

class MouseListener
{
public:
	MouseListener(const MouseListener& mouseListener) = delete;

	static MouseListener* Get();
	static void MousePosCallback(GLFWwindow* window, double posX, double posY);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	static void EndFrame();
	static float GetX();
	static float GetY();
	static float GetDx();
	static float GetDy();
	static float GetScrollX();
	static float GetScrollY();
	static bool GetMouseButtonPressed(int button);
	static bool GetMouseButtonClicked(int button);

private:
	MouseListener();

	static MouseListener* m_instance;
	float m_scrollX, m_scrollY;
	float m_posX, m_posY, m_lastY, m_lastX; // lastX, Y for dx and dy
	bool m_mouseButtonPressed[3] = { false };
	bool m_mouseButtonClicked[3] = { false };
};